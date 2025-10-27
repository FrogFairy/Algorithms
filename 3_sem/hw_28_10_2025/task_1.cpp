#include <vector>
#include <iostream>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        map<string, vector<string>> graph;
        stack<string> result;

        for (vector<string>& pair : tickets)
        {
            graph[pair[0]].push_back(pair[1]);
        }

        for (auto& [from, to] : graph)
        {
            sort(to.begin(), to.end());
        }

        dfs("JFK", graph, result);

        vector<string> out;
        while (!result.empty())
        {
            out.push_back(result.top());
            result.pop();
        }
        return out;
    }

    void dfs(string u, map<string, vector<string>>& graph, stack<string>& result)
    {
        while (!graph[u].empty())
        {
            string v = graph[u][0];
            graph[u].erase(graph[u].begin());
            dfs(v, graph, result);
        }
        result.push(u);
    }
};

int main()
{
    vector<vector<string>> tickets = {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
    Solution solution;
    solution.findItinerary(tickets);
}