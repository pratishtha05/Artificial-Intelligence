#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// Directions: up, down, left, right
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

// Node
struct Node {
    int x, y, g, h, f;
    Node(int x, int y, int g, int h) : x(x), y(y), g(g), h(h), f(g + h) {}
    bool operator>(const Node& other) const { return f > other.f; }
};

// Heuristic: Manhattan distance
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* algorithm
vector<pair<int, int>> solve(vector<vector<int>>& grid, int n, int sx, int sy, int destX, int destY) {
    if (sx == destX && sy == destY) {
        return {{sx, sy}};
    }

    vector<vector<int>> g(n, vector<int>(n, INT_MAX));

    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(n, {-1, -1}));
    
    priority_queue<Node, vector<Node>, greater<Node>> pq;

   
    g[sx][sy] = 0;
    int h = heuristic(sx, sy, destX, destY);
    pq.push(Node(sx, sy, 0, h));

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        int x = node.x, y = node.y;

        if (x == destX && y == destY) {
            vector<pair<int, int>> path;
            while (x != -1 && y != -1) {
                path.push_back({x, y});
                auto p = parent[x][y];
                x = p.first;
                y = p.second;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny] == 1) {
                continue;
            }

            int tentativeG = g[x][y] + 1;

            if (tentativeG < g[nx][ny]) {
                g[nx][ny] = tentativeG;
                int h = heuristic(nx, ny, destX, destY);
                pq.push(Node(nx, ny, tentativeG, h));
                parent[nx][ny] = {x, y}; 
            }
        }
    }

    return {};
}

void printGrid(const vector<vector<int>>& grid, const vector<pair<int, int>>& path, int n) {
    vector<vector<char>> vis(n, vector<char>(n, '.'));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                vis[i][j] = '#';
            }
        }
    }

    for (int i = 0; i < path.size(); i++) {
        int x = path[i].first;
        int y = path[i].second;
        if (i == 0) {
            vis[x][y] = 'S'; 
        } else if (i == path.size() - 1) {
            vis[x][y] = 'D'; 
        } else {
            vis[x][y] = '*';
        }
    }

    cout << "\n=== Grid Visualization ===\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << vis[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter grid size (n): ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid grid size!\n";
        return 1;
    }

    int sx, sy, dx, dy;
    cout << "Enter start coordinates (sx sy): ";
    cin >> sx >> sy;
    cout << "Enter destination coordinates (dx dy): ";
    cin >> dx >> dy;

    auto valid = [&](int x, int y) -> bool {
        return x >= 0 && y >= 0 && x < n && y < n;
    };

    if (!valid(sx, sy) || !valid(dx, dy)) {
        cout << "Start or destination is out of bounds!\n";
        return 1;
    }

    vector<vector<int>> grid(n, vector<int>(n, 0));

    int obs;
    cout << "How many obstacles? ";
    cin >> obs;

    for (int k = 0; k < obs; k++) {
        int x, y;
        cout << "Obstacle " << k + 1 << " (x y): ";
        cin >> x >> y;

        if (!valid(x, y)) {
            cout << "Invalid coordinates! Try again.\n";
            k--; 
            continue;
        }

        if ((x == sx && y == sy) || (x == dx && y == dy)) {
            cout << "Cannot place obstacle on start or destination!\n";
            k--;
            continue;
        }

        grid[x][y] = 1;
    }

    vector<pair<int, int>> path = solve(grid, n, sx, sy, dx, dy);

    if (path.empty()) {
        cout << "\n No path found from S to D!\n";
    } else {
        cout << "\n Path found!\n";
        cout << "Total Cost (number of steps): " << path.size() - 1 << endl;
        cout << "Path: ";
        for (const auto& p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
        printGrid(grid, path, n);
    }

    return 0;
}