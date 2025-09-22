#include <vector>

inline bool has_cycle(const std::vector<std::vector<int>> &g)
{
    std::vector<bool> visited(g.size(), false);
    std::function<bool(int,int)> dfs = [&](int v,int parent_v)
    {
        visited[v] = true;
        for(int u : g[v])
            if( u != parent_v && (visited[u] || dfs(u,v)) )
                return true;
        return false;
    };
    for(int v = 0; v < g.size() ; ++v)
        if(!visited[v] && dfs(v,-1))
            return true;
    return false;
}

inline bool has_path(const std::vector<std::vector<int>> &g, int v1, int v2)
{
    std::vector<bool> visited(g.size(), false);
    std::function<bool(int)> dfs = [&](int v1, int v2)
    {
        visited[v1] = true;
        for(int u : g[v1])
            if(!visited[u] && (u == v2 || dfs(u, v2)))
                return true;
        return false;
    };
    return dfs(v1, v2);
}

inline std::vector<int> get_path(const std::vector<std::vector<int>> &g, int v1, int v2)
{
    if (!has_path(g, v1, v2))
        return false;
    std::vector<bool> visited(g.size(), false);
    std::vector<int> path;
    std::function<bool(int)> dfs = [&](int v1, int v2)
    {
        visited[v1] = true;
        for(int u : g[v1])
        {
            if(!visited[u])
            {
                if(u == v2)
                    path.push_back(u);
            }
                
            std::vector<int> dfs_path = dfs(u, v2);
            path.insert(path.end(), dfs_path.begin(), dfs_path.end());
        }
    };
    return path;
}