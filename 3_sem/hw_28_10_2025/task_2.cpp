#include <vector>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, stack<int>> graph;
        unordered_map<int, int> degree;

        for (const auto& p : pairs)
        {
            int u = p[0], v = p[1];
            graph[u].push(v);
            degree[u]++;
            degree[v]--;
        }

        int start = pairs[0][0];
        for (const auto& [node, deg] : degree) {
            if (deg == 1) {
                start = node;
                break;
            }
        }

        vector<int> path = dfs(start, graph);
        vector<vector<int>> result;
        for (int i = 0; i < path.size() - 1; i++) {
            result.push_back({path[i], path[i + 1]});
        }
        
        return result;
    }

    vector<int> dfs(int start, unordered_map<int, stack<int>>& graph)
    {
        vector<int> path;
        stack<int> st;
        st.push(start);
        
        while (!st.empty()) {
            int node = st.top();
            if (!graph[node].empty()) {
                int next = graph[node].top();
                graph[node].pop();
                st.push(next);
            } else {
                path.push_back(node);
                st.pop();
            }
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> pairs = {{1,2},{1,3},{2,1}};
    vector<vector<int>> path = solution.validArrangement(pairs);
    for (vector<int>& el : path)
    {
        cout << el[0] << " " << el[1] << endl;
    }
    cout << endl;
}