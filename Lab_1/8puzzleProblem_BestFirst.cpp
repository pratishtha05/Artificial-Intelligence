#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

// Goal state
vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Directions for blank movement (up, down, left, right)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Convert 2D puzzle state to string for hashing
string toString(vector<vector<int>> v) {
    string s = "";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            s += to_string(v[i][j]);
    return s;
}

// Print puzzle state
void printPuzzle(vector<vector<int>> v) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << v[i][j] << " ";
        cout << "\n";
    }
    cout << "------\n";
}

// Find blank (0) position
pair<int, int> findZero(vector<vector<int>> &v) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (v[i][j] == 0)
                return make_pair(i, j);
    return make_pair(-1, -1);
}

// Heuristic: count number of misplaced tiles
int heuristic(vector<vector<int>> &v) {
    int h = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (v[i][j] != 0 && v[i][j] != goal[i][j])
                h++;
    return h;
}

// Structure for priority queue nodes
struct Node {
    vector<vector<int>> state;
    int cost; // heuristic value
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

// Best-First Search implementation
void solvePuzzleBestFirst(vector<vector<int>> start) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, string> parent;
    unordered_map<string, bool> visited;

    Node startNode = {start, heuristic(start)};
    pq.push(startNode);
    visited[toString(start)] = true;
    parent[toString(start)] = "";

    int steps = 0;

    while (!pq.empty()) {
        Node currNode = pq.top();
        pq.pop();
        vector<vector<int>> curr = currNode.state;

        steps++;

        if (curr == goal) {
            cout << "Goal state reached!\n";
            vector<string> path;
            string key = toString(curr);

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
            cout << "Nodes Expanded: " << steps << "\n";
            return;
        }

        pair<int, int> pos = findZero(curr);
        int x = pos.first;
        int y = pos.second;

        // Generate next possible states
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> next = curr;
                swap(next[x][y], next[nx][ny]);

                string nextStr = toString(next);
                if (!visited[nextStr]) {
                    visited[nextStr] = true;
                    parent[nextStr] = toString(curr);
                    int h = heuristic(next);
                    pq.push({next, h});
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

    solvePuzzleBestFirst(start);
    return 0;
}
