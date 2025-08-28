#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

string toStr(const vector<int>& board) {
    string s;
    for (int tile : board) s += to_string(tile);
    return s;
}

void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

vector<int> target = {1, 2, 3, 4, 5, 6, 7, 8, 0};
set<string> visited;
vector<vector<int>> path;  

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};


bool dfs(vector<int> board, int depth = 0, int maxDepth = 15) {
    string state = toStr(board);
    
    if (depth > maxDepth) return false;
    if (visited.find(state) != visited.end()) return false;

    visited.insert(state);
    path.push_back(board);

    if (board == target) {
        return true;
    }

    int idx = 0;
    while (board[idx] != 0) idx++;
    int x = idx / 3, y = idx % 3;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;

        int nidx = nx * 3 + ny;
        vector<int> newBoard = board;
        swap(newBoard[idx], newBoard[nidx]);

        if (dfs(newBoard, depth + 1, maxDepth)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

int main() {
    vector<int> start(9);
    cout << "Enter 8-puzzle initial state (use 0 for blank):\n";
    for (int i = 0; i < 9; i++) {
        cin >> start[i];
    }

    cout << "\nInitial State:\n";
    printBoard(start);

    vector<int> temp;
    int inv = 0;
    for (int x : start) if (x != 0) temp.push_back(x);
    for (int i = 0; i < 8; i++)
        for (int j = i + 1; j < 8; j++)
            if (temp[i] > temp[j]) inv++;
    if (inv % 2 != 0) {
        cout << "This puzzle is not solvable!\n";
        return 0;
    }

    bool solved = false;
    for (int maxDepth = 10; maxDepth <= 30; maxDepth += 5) {
        visited.clear();
        path.clear();
        cout << "Trying DFS with max depth = " << maxDepth << "...\n";
        if (dfs(start, 0, maxDepth)) {
            solved = true;
            break;
        }
    }

    if (solved) {
        cout << "\n Solved!\n";
        cout << "Solution Path (moves = " << path.size() - 1 << "):\n";
        for (int i = 0; i < path.size(); i++) {
            cout << "Step " << i << ":\n";
            printBoard(path[i]);
        }
    } else {
        cout << "\n No solution found within depth limit.\n";
    }

    return 0;
}