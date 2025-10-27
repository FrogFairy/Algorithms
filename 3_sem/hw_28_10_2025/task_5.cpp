#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int countPaths(const vector<vector<int>>& graph, int start, int end) {
    if (start == end) return 1;
    int n = graph.size();
    
    vector<int> dist(n, -1);
    vector<int> count(n, 0);
    
    dist[start] = 0;
    count[start] = 1;
    
    queue<int> q;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                count[v] = count[u];
                q.push(v);
            }
            else if (dist[v] == dist[u] + 1) {
                count[v] += count[u];
            }
        }
    }
    
    return count[end];
}


int main()
{
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0, 4}, {1, 5}, {1, 2, 5}, {3, 4}};
    cout << countPaths(graph, 0, 5) << endl;
}