#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    string input;
    vector<string> lines;
    
    while (getline(cin, input)) {
        if (input.empty()) continue;
        lines.push_back(input);
    }
    
    int n = lines.size();
    if (n == 0) {
        cout << "0" << endl;
        return 0;
    }
    
    int m = lines[0].size();
    
    vector<string> map = lines;
    
    queue<Point> q;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 'W') {
                q.push(Point(i, j));
                dist[i][j] = 0;
            }
        }
    }
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    int maxTime = 0;
    
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        
        int x = current.x;
        int y = current.y;
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (map[nx][ny] == 'L' && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    maxTime = max(maxTime, dist[nx][ny]);
                    q.push(Point(nx, ny));
                }
            }
        }
    }
    
    cout << maxTime << endl;
    
    return 0;
}