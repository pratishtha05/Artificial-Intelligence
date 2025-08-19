#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
using namespace std;

vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

string toString(vector<vector<int>> v) {
    string s = "";
    for (auto &row : v)
        for (auto &x : row)
            s += to_string(x);
    return s;
}

void printPuzzle(vector<vector<int>> v) {
    for (auto &row : v) {
        for (auto &x : row)
            cout << x << " ";
        cout << "\n";
    }
    cout << "------\n";
}

pair<int, int> findZero(vector<vector<int>> &v) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (v[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

void solvePuzzle(vector<vector<int>> start) {
    queue<vector<vector<int>>> q;
    unordered_map<string, string> parent;
    unordered_map<string, bool> visited;

    q.push(start);
    visited[toString(start)] = true;
    parent[toString(start)] = "";

    while (!q.empty()) {
        vector<vector<int>> curr = q.front();
        q.pop();

        if (curr == goal) {
            cout << "Goal state reached!\n";
            vector<string> path;
            string key = toString(curr);

            while (key != "") {
                vector<vector<int>> temp(3, vector<int>(3));
                for (int i = 0, k = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++, k++)
                        temp[i][j] = key[k] - '0';
                path.push_back(key);
                key = parent[key];
            }

            reverse(path.begin(), path.end());
            cout << "Steps to reach goal:\n";
            for (auto &p : path) {
                vector<vector<int>> temp(3, vector<int>(3));
                for (int i = 0, k = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++, k++)
                        temp[i][j] = p[k] - '0';
                printPuzzle(temp);
            }
            cout << "Total Moves: " << path.size() - 1 << "\n";
            return;
        }

        pair<int, int> pos = findZero(curr);
        int x = pos.first;
        int y = pos.second;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> next = curr;
                swap(next[x][y], next[nx][ny]);

                string stateStr = toString(next);
                if (!visited[stateStr]) {
                    visited[stateStr] = true;
                    parent[stateStr] = toString(curr);
                    q.push(next);
                }
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));

    cout << "Enter the initial 8-puzzle state (use 0 for blank):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    solvePuzzle(start);
    return 0;
}
