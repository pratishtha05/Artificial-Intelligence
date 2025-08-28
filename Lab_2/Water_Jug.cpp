#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void solveWaterJug(int capA, int capB, int target) {
    if (target > capA && target > capB) {
        cout << "Target exceeds both jug capacities!\n";
        return;
    }

    if (target % gcd(capA, capB) != 0) {
        cout << "No solution exists (mathematical condition fails).\n";
        return;
    }

    set<pair<int, int>> visited;
    queue<vector<pair<int, int>>> q;

    vector<pair<int, int>> path;
    path.push_back({0, 0});
    q.push(path);
    visited.insert({0, 0});

    while (!q.empty()) {
        vector<pair<int, int>> currPath = q.front();
        q.pop();

        int a = currPath.back().first;
        int b = currPath.back().second;

        if (a == target || b == target) {
            cout << "Steps to achieve " << target << " liters:\n";
            for (auto& state : currPath) {
                cout << "(" << state.first << "," << state.second << ")\n";
            }
            return;
        }

        vector<pair<int, int>> nextStates = {
            {capA, b},           // 1. Fill A
            {a, capB},           // 2. Fill B
            {0, b},              // 3. Empty A
            {a, 0},              // 4. Empty B
            {a - min(a, capB - b), b + min(a, capB - b)}, // 5. Pour A → B
            {a + min(b, capA - a), b - min(b, capA - a)}  // 6. Pour B → A
        };

        for (auto& ns : nextStates) {
            pair<int, int> key = ns;
            if (visited.find(key) == visited.end()) {
                visited.insert(key);
                vector<pair<int, int>> newPath = currPath;
                newPath.push_back(ns);
                q.push(newPath);
            }
        }
    }

    cout << "No solution found!\n"; 
}

int main() {
    int capA, capB, target;
    cout << "Enter Jug A capacity: "; cin >> capA;
    cout << "Enter Jug B capacity: "; cin >> capB;
    cout << "Enter target amount: "; cin >> target;

    solveWaterJug(capA, capB, target);

    return 0;
}