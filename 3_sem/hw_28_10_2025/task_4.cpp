#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs1(int v, vector<vector<int>>& graph,
        vector<bool>& visited, stack<int>& order) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs1(u, graph, visited, order);
        }
    }
    order.push(v);
}

void dfs2(int v, vector<vector<int>>& reverse_graph,
        vector<bool>& visited, vector<int>& comp, int comp_id) {
    visited[v] = true;
    comp[v] = comp_id;
    for (int u : reverse_graph[v]) {
        if (!visited[u]) {
            dfs2(u, reverse_graph, visited, comp, comp_id);
        }
    }
}

vector<vector<int>> reverseGraph(vector<vector<int>>& graph)
{
    vector<vector<int>> result(graph.size(), vector<int>{});
    for (int i = 0; i < graph.size(); ++i)
    {
        for (int v : graph[i])
        {
            result[v].push_back(i);
        }
    }
    return result;
}

pair<vector<int>, int> findSCC(vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false);
    stack<int> order;
    
    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            dfs1(i, graph, visited, order);
        }
    }
    fill(visited.begin(), visited.end(), false);
    vector<int> comp(graph.size(), -1);
    int comp_count = 0;
    auto reverse_graph = reverseGraph(graph);
    
    while (!order.empty()) {
        int v = order.top();
        order.pop();
        
        if (!visited[v]) {
            dfs2(v, reverse_graph, visited, comp, comp_count);
            comp_count++;
        }
    }
    
    return {comp, comp_count};
}

int minEdges(vector<vector<int>>& graph) {
    auto [comp, comp_count] = findSCC(graph);
    
    if (comp_count == 1) {
        return 0;
    }
    
    vector<int> in_degree(comp_count, 0);
    vector<int> out_degree(comp_count, 0);
    
    for (int u = 0; u < graph.size(); u++) {
        for (int v : graph[u]) {
            if (comp[u] != comp[v]) {
                out_degree[comp[u]]++;
                in_degree[comp[v]]++;
            }
        }
    }
    
    int sources = 0, sinks = 0;
    for (int i = 0; i < comp_count; i++) {
        if (in_degree[i] == 0) sources++;
        if (out_degree[i] == 0) sinks++;
    }
    
    return max(sources, sinks);
}

int main()
{
    vector<vector<int>> graph = {{1}, {2, 3}, {0}, {4}, {}};
    cout << minEdges(graph) << endl;
}