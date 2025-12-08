#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int start_x = -1, start_y = -1;
        int total_keys = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@') {
                    start_x = i;
                    start_y = j;
                } else if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    total_keys = max(total_keys, grid[i][j] - 'a' + 1);
                }
            }
        }
        
        int allKeysMask = (1 << total_keys) - 1;
        
        queue<tuple<int, int, int>> q;
        q.push({start_x, start_y, 0});
        
        unordered_set<string> visited;
        visited.insert(to_string(start_x) + "," + to_string(start_y) + ",0");
        
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                auto [x, y, mask] = q.front();
                q.pop();
                
                if (mask == allKeysMask) {
                    return steps;
                }
                
                for (auto& dir : directions) {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    int newMask = mask;
                    
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                        continue;
                    }
                    
                    char cell = grid[nx][ny];
                    
                    if (cell == '#') {
                        continue;
                    }
                    
                    // Если это замок и у нас нет ключа
                    if (cell >= 'A' && cell <= 'F') {
                        int lockNum = cell - 'A';
                        if (!(mask & (1 << lockNum))) {
                            continue;
                        }
                    }
                    
                    // Если это ключ, добавляем его
                    if (cell >= 'a' && cell <= 'f') {
                        int keyNum = cell - 'a';
                        newMask |= (1 << keyNum);
                    }
                    
                    string state = to_string(nx) + "," + to_string(ny) + "," + to_string(newMask);
                    
                    if (visited.find(state) == visited.end()) {
                        visited.insert(state);
                        q.push({nx, ny, newMask});
                    }
                }
            }
            
            steps++;
        }
        
        return -1;
    }
};

// int main() {
//     Solution sol;
    
//     vector<string> grid1 = {"@.a..","###.#","b.A.B"};
//     cout << sol.shortestPathAllKeys(grid1) << endl; // 8
    
//     vector<string> grid2 = {"@..aA","..B#.","....b"};
//     cout << sol.shortestPathAllKeys(grid2) << endl; // 6
    
//     return 0;
// }