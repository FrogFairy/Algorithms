#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<bool> visited(isConnected.size(), false);
        int provinces = 0;
        for (int i = 0; i < isConnected.size(); ++i)
        {
            if (!visited[i])
            {
                provinces++;
                dfs(isConnected, visited, i);
            }
        }

        return provinces;
    }

    void dfs(vector<vector<int>>& isConnected, vector<bool>& visited, int u) {
        visited[u] = true;
        for (int v = 0; v < isConnected.size(); v++) {
            if (isConnected[u][v] == 1 && !visited[v]) {
                dfs(isConnected, visited, v);
            }
        }
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> isConnected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    cout << solution.findCircleNum(isConnected) << endl;
}