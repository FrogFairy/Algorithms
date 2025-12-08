#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

void recover_maze(Point start, Point exit, 
                vector<vector<Point>>& parent, vector<string>& maze) {
    vector<Point> path;
    Point current = exit;
    
    while (!(current.x == start.x && current.y == start.y)) {
        path.push_back(current);
        current = parent[current.x][current.y];
    }

    for (const auto& p : path) {
        if (maze[p.x][p.y] != 'S') {
            maze[p.x][p.y] = 'o';
        }
    }
}

int main() {
    string input_map;
    
    string line;
    while (getline(cin, line)) {
        input_map += line + "\n";
    }
    
    if (!input_map.empty() && input_map.back() == '\n') {
        input_map.pop_back();
    }
    
    vector<string> maze;
    size_t pos = 0;
    while ((pos = input_map.find('\n')) != string::npos) {
        maze.push_back(input_map.substr(0, pos));
        input_map.erase(0, pos + 1);
    }
    if (!input_map.empty()) {
        maze.push_back(input_map);
    }
    
    int n = maze.size();
    if (n == 0) {
        cout << "Empty maze!" << endl;
        return 0;
    }
    int m = maze[0].size();
    
    Point start(-1, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == 'S') {
                start = Point(i, j);
                break;
            }
        }
        if (start.x != -1) break;
    }
    
    if (start.x == -1) {
        cout << "No start point found!" << endl;
        return 0;
    }
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<Point>> parent(n, vector<Point>(m, Point(-1, -1)));
    queue<Point> q;
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    q.push(start);
    visited[start.x][start.y] = true;
    Point exit(-1, -1);
    bool found_exit = false;
    
    while (!q.empty() && !found_exit) {
        Point current = q.front();
        q.pop();
        
        if (current.x == 0 || current.x == n-1 || current.y == 0 || current.y == m-1) {
            if (maze[current.x][current.y] != '#') {
                exit = current;
                found_exit = true;
                break;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (!visited[nx][ny] && maze[nx][ny] != '#') {
                    visited[nx][ny] = true;
                    parent[nx][ny] = current;
                    q.push(Point(nx, ny));
                }
            }
        }
    }
    
    if (!found_exit) {
        for (const auto& row : maze) {
            cout << row << endl;
        }
        return 0;
    }
    
    recover_maze(start, exit, parent, maze);

    for (const auto& row : maze) {
        cout << row << endl;
    }
    
    return 0;
}