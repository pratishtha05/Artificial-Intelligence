#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

// Goal state for reference
vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Directions for moving the blank space (up, down, left, right)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Convert 2D vector to string (for hashing and visited tracking)
string toString(vector<vector<int>> v) {
    string s = "";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            s += to_string(v[i][j]);
    return s;
}

// Print the puzzle state
void printPuzzle(vector<vector<int>> v) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << v[i][j] << " ";
        cout << "\n";
    }
    cout << "------\n";
}

// Find position of 0 (blank)
pair<int, int> findZero(vector<vector<int>> &v) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (v[i][j] == 0)
                return make_pair(i, j);
    return make_pair(-1, -1);
}

// DFS search (iterative version)
void solvePuzzleDFS(vector<vector<int>> start) {
    stack<vector<vector<int>>> st;
    unordered_map<string, string> parent; // to reconstruct path
    unordered_map<string, bool> visited;

    st.push(start);
    visited[toString(start)] = true;
    parent[toString(start)] = "";

    int maxDepth = 50; // limit depth to prevent infinite recursion
    unordered_map<string, int> depth;
    depth[toString(start)] = 0;

    while (!st.empty()) {
        vector<vector<int>> curr = st.top();
        st.pop();

        string currStr = toString(curr);
        int currDepth = depth[currStr];

        if (curr == goal) {
            cout << "Goal state reached!\n";
            vector<string> path;
            string key = currStr;

            while (key != "") {
                path.push_back(key);
                key = parent[key];
            }

            reverse(path.begin(), path.end());
            cout << "Steps to reach goal:\n";
            for (int p = 0; p < (int)path.size(); p++) {
                vector<vector<int>> temp(3, vector<int>(3));
                for (int i = 0, k = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++, k++)
                        temp[i][j] = path[p][k] - '0';
                printPuzzle(temp);
            }
            cout << "Total Moves: " << path.size() - 1 << "\n";
            return;
        }

        if (currDepth >= maxDepth)
            continue;

        pair<int, int> pos = findZero(curr);
        int x = pos.first;
        int y = pos.second;

        // Explore 4 directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> next = curr;
                swap(next[x][y], next[nx][ny]);

                string nextStr = toString(next);
                if (!visited[nextStr]) {
                    visited[nextStr] = true;
                    parent[nextStr] = currStr;
                    depth[nextStr] = currDepth + 1;
                    st.push(next);
                }
            }
        }
    }

    cout << "No solution found within depth limit.\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));
    cout << "Enter the initial 8-puzzle state (use 0 for blank):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    solvePuzzleDFS(start);
    return 0;
}
