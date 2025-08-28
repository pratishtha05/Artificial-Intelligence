#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const vector<int> target = {1, 2, 3, 4, 5, 6, 7, 8, 0};

void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

int misplaced(const vector<int>& board) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] != 0 && board[i] != target[i])
            count++;
    }
    return count;
}

vector<vector<int>> getNeighbors(const vector<int>& board) {
    vector<vector<int>> neighbors;
    int idx = 0;
    while (board[idx] != 0) idx++; 
    int x = idx / 3, y = idx % 3;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;

        int nidx = nx * 3 + ny;
        vector<int> next = board;
        neighbors.push_back(next);
    }

    return neighbors;
}

void hillClimbing(vector<int> start) {
    vector<int> current = start;
    int steps = 0;

    cout << "Starting Hill Climbing...\n";
    while (true) {
        int currentH = misplaced(current);

        if (currentH == 0) {
            cout << "\n Puzzle solved in " << steps << " steps!\n";
            cout << "Final State:\n";
            printBoard(current);
            return;
        }

        vector<vector<int>> neighbors = getNeighbors(current);
        vector<int> bestNext;
        int bestH = currentH;

        for (auto& next : neighbors) {
            int h = misplaced(next);
            if (h < bestH) {
                bestH = h;
                bestNext = next;
            }
        }

        if (bestH == currentH) {
            cout << "\n Stuck in local minimum!\n";
            cout << "Current heuristic (misplaced tiles): " << currentH << "\n";
            cout << "Cannot improve further.\n";
            cout << "Final (unsolved) state:\n";
            printBoard(current);
            return;
        }

        current = bestNext;
        steps++;
        cout << "Step " << steps << " | Misplaced: " << bestH << endl;
    }
}

bool isSolvable(vector<int> board) {
    vector<int> temp;
    int inv = 0;
    for (int x : board) if (x != 0) temp.push_back(x);
    for (int i = 0; i < 8; i++)
        for (int j = i + 1; j < 8; j++)
            if (temp[i] > temp[j]) inv++;
    return inv % 2 == 0;
}

int main() {
    vector<int> start(9);
    cout << "Enter 8-puzzle initial state (use 0 for blank), row by row:\n";
    for (int i = 0; i < 9; i++) {
        cin >> start[i];
    }

    cout << "\nInitial State:\n";
    printBoard(start);

    if (!isSolvable(start)) {
        cout << "This puzzle is not solvable!\n";
        return 0;
    }

    hillClimbing(start);

    return 0;
}