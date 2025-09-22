#include <iostream>
#include <vector>
#include <bits/stdc++.h>

bool dfs(std::vector<std::vector<int>>& g, int v, int color, std::vector<int>& colors)
{
    colors[v] = color;
    for(int u : g[v])
    {
        if(colors[u] == -1)
        {
            if(!dfs(g, u, 1 - color, colors))
            {
                return false;
            }
        }
        else if(colors[u] == color)
        {
            return false;
        }
    }
    return true;
};

int main()
{
    int V, E;
    std::cin >> V >> E;
    std::vector<std::vector<int>> result(V, std::vector<int>());
    for (int i = 0; i < E; ++i)
    {
        int S, D;
        std::cin >> S >> D;
        result[S].push_back(D);
        result[D].push_back(S);
    }

    std::vector<int> colors(V, -1);
    bool isBipartite = true;
    
    for (int i = 0; i < V; ++i)
    {
        if (colors[i] == -1)
        {
            if (!dfs(result, i, 0, colors))
            {
                isBipartite = false;
                break;
            }
        }
    }
    
    if (isBipartite)
    {
        std::cout << "Graph is bipartite" << std::endl;
    }
    else
    {
        std::cout << "Graph is not bipartite" << std::endl;
    }
    
    return 0;
}