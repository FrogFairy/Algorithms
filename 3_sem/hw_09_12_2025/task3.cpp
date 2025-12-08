#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

vector<vector<int>> bfs(const vector<string>& maze, Point start) {
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<Point> q;
    
    dist[start.x][start.y] = 0;
    q.push(start);
    
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] != '#') {
                if (dist[nx][ny] > dist[current.x][current.y] + 1) {
                    dist[nx][ny] = dist[current.x][current.y] + 1;
                    q.push(Point(nx, ny));
                }
            }
        }
    }
    
    return dist;
}

int main() {
    string input;
    vector<string> lines;
    
    while (getline(cin, input)) {
        if (input.empty()) break;
        lines.push_back(input);
    }
    
    int n = lines.size();
    int m = lines[0].size();
    
    Point A_pos, B_pos, F_pos;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] == 'A') {
                A_pos = Point(i, j);
            } else if (lines[i][j] == 'B') {
                B_pos = Point(i, j);
            } else if (lines[i][j] == 'F') {
                F_pos = Point(i, j);
            }
        }
    }
    
    vector<vector<int>> dist_A = bfs(lines, A_pos);
    vector<vector<int>> dist_B = bfs(lines, B_pos);
    vector<vector<int>> dist_F = bfs(lines, F_pos);
    
    int min_total = INT_MAX;
    Point best_M;
    bool found = false;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (lines[i][j] != '#') {
                if (dist_A[i][j] != INT_MAX && 
                    dist_B[i][j] != INT_MAX && 
                    dist_F[i][j] != INT_MAX) {
                    
                    int total = dist_A[i][j] + dist_B[i][j] + dist_F[i][j];
                    if (total < min_total) {
                        min_total = total;
                        best_M = Point(i, j);
                        found = true;
                    }
                }
            }
        }
    }
    
    vector<string> result = lines;
    Point current = best_M;
    
    while (!(current == A_pos)) {
        if (!(current == best_M) && !(current == F_pos)) {
            result[current.x][current.y] = 'o';
        }
        
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        bool moved = false;
        
        for (int i = 0; i < 4 && !moved; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (dist_A[nx][ny] == dist_A[current.x][current.y] - 1) {
                    current = Point(nx, ny);
                    moved = true;
                }
            }
        }
    }
    
    current = best_M;
    while (!(current == B_pos)) {
        if (!(current == best_M) && !(current == F_pos)) {
            result[current.x][current.y] = 'o';
        }
        
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        bool moved = false;
        
        for (int i = 0; i < 4 && !moved; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (dist_B[nx][ny] == dist_B[current.x][current.y] - 1) {
                    current = Point(nx, ny);
                    moved = true;
                }
            }
        }
    }
    
    if (!(best_M == F_pos)) {
        current = best_M;
        while (!(current == F_pos)) {
            if (!(current == best_M)) {
                result[current.x][current.y] = 'o';
            }
            
            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};
            bool moved = false;
            
            for (int i = 0; i < 4 && !moved; i++) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (dist_F[nx][ny] == dist_F[current.x][current.y] - 1) {
                        current = Point(nx, ny);
                        moved = true;
                    }
                }
            }
        }
    }
    
    for (const auto& line : result) {
        cout << line << endl;
    }
    
    return 0;
}