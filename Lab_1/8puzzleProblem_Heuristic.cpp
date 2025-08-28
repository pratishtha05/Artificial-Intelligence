#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

const vector<int> target = {1, 2, 3, 4, 5, 6, 7, 8, 0};

string toString(const vector<int>& board) {
    string s;
    for (int tile : board) s += (char)(tile + '0');
    return s;
}

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

struct Node {
    vector<int> board;
    int h;

    Node(vector<int> b) : board(b), h(misplaced(b)) {}

    bool operator>(const Node& other) const {
        return h > other.h;
    }
};

void solve8Puzzle(vector<int> start) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<string> visited;

    pq.push(Node(start));
    visited.insert(toString(start));

    int moves = 0;
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        vector<int> curr = node.board;

        if (curr == target) {
            cout << "\n Solved!\n";
            cout << "Final State:\n";
            printBoard(curr);
            return;
        }

        int idx = 0;
        while (curr[idx] != 0) idx++;
        int x = idx / 3, y = idx % 3;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;

            int nidx = nx * 3 + ny;
            vector<int> next = curr;
            swap(next[idx], next[nidx]); 

            string ns = toString(next);
            if (visited.find(ns) == visited.end()) {
                visited.insert(ns);
                pq.push(Node(next));
            }
        }

        moves++;
        if (moves > 10000) {
            cout << "Search taking too long... likely stuck.\n";
            break;
        }
    }

    cout << "No solution found (may be unsolvable or heuristic got stuck).\n";
}

int main() {
    vector<int> start(9);
    cout << "Enter 8-puzzle initial state (use 0 for blank), row by row:\n";
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

    solve8Puzzle(start);

    return 0;
}