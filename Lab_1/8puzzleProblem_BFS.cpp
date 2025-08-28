#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

string boardToString(const vector<int>& board) {
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

void solve8Puzzle(vector<int> start) {
    vector<int> target = {1, 2, 3, 4, 5, 6, 7, 8, 0}; 
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};

    queue<vector<int>> q;
    set<string> visited;

    q.push(start);
    visited.insert(boardToString(start));

    int moves = 0;
    while (!q.empty()) {
        int size = q.size();
        cout << "BFS Level (moves = " << moves << "), states at this level: " << size << endl;

        while (size--) {
            vector<int> curr = q.front(); q.pop();

            if (curr == target) {
                cout << "\n✅ Solved in " << moves << " moves!\n";
                cout << "Final State:\n";
                printBoard(curr);
                return;
            }

            int idx = -1;
            for (int i = 0; i < 9; i++) {
                if (curr[i] == 0) {
                    idx = i;
                    break;
                }
            }
            int x = idx / 3, y = idx % 3;

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i], nidx = nx * 3 + ny;
                if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;

                vector<int> next = curr;
                swap(next[idx], next[nidx]); 

                string ns = boardToString(next);
                if (visited.find(ns) == visited.end()) {
                    visited.insert(ns);
                    q.push(next);
                }
            }
        }
        moves++;
    }

    cout << "No solution found!\n";
}

int main() {
    vector<int> start(9);
    cout << "Enter initial 8-puzzle state (use 0 for blank), row by row:\n";
    for (int i = 0; i < 9; i++) {
        cin >> start[i];
    }

    cout << "\nInitial State:\n";
    printBoard(start);

    solve8Puzzle(start);

    return 0;
}