#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
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

// Convert 2D vector to string (for easy printing/debugging)
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

// Heuristic: number of misplaced tiles
int heuristic(vector<vector<int>> &v) {
    int h = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (v[i][j] != 0 && v[i][j] != goal[i][j])
                h++;
    return h;
}

// Generate all possible neighbor states
vector<vector<vector<int>>> getNeighbors(vector<vector<int>> &curr) {
    vector<vector<vector<int>>> neighbors;
    pair<int, int> pos = findZero(curr);
    int x = pos.first, y = pos.second;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            vector<vector<int>> next = curr;
            swap(next[x][y], next[nx][ny]);
            neighbors.push_back(next);
        }
    }
    return neighbors;
}

// Hill Climbing Algorithm
void solvePuzzleHillClimbing(vector<vector<int>> start) {
    srand(time(0)); // for random tie-breaking

    vector<vector<int>> current = start;
    int current_h = heuristic(current);

    cout << "Initial State (Heuristic = " << current_h << "):\n";
    printPuzzle(current);

    int steps = 0;

    while (true) {
        if (current == goal) {
            cout << "Goal reached successfully!\n";
            cout << "Total Steps: " << steps << "\n";
            return;
        }

        vector<vector<vector<int>>> neighbors = getNeighbors(current);

        vector<vector<int>> nextState = current;
        int best_h = current_h;

        // Find neighbor with best heuristic (lowest)
        for (auto &n : neighbors) {
            int h = heuristic(n);
            if (h < best_h) {
                best_h = h;
                nextState = n;
            }
        }

        // If no better neighbor found → stuck in local minima
        if (best_h >= current_h) {
            cout << "Stuck in local minimum or plateau.\n";
            cout << "Final State (Heuristic = " << current_h << "):\n";
            printPuzzle(current);
            return;
        }

        // Move to better neighbor
        current = nextState;
        current_h = best_h;
        steps++;

        cout << "Step " << steps << " (Heuristic = " << current_h << "):\n";
        printPuzzle(current);
    }
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));
    cout << "Enter the initial 8-puzzle state (use 0 for blank):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    solvePuzzleHillClimbing(start);
    return 0;
}
