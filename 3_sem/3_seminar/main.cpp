#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <functional>

inline std::vector<int> topological_sort(const std::vector<std::vector<int>> &g, bool check_cycle = true)
{
    // if(check_cycle && dir_has_cycle(g))
    //     return {};
    std::vector<bool> visited(g.size());
    std::vector<int> sorted;
    std::function<void(int)> dfs = [&](int v)
    {
        visited[v] = true;
        for(int u : g[v])
            if(!visited[u])
                dfs(u);
        sorted.push_back(v);
    };
    for(int v = 0; v < g.size() ; ++v)
        if(!visited[v])
            dfs(v);
    std::reverse(sorted.begin(),sorted.end());
    return sorted;
}

int main()
{
    std::map<std::string, int> Clothes = {
        {"watch", 0},
        {"socks", 1},
        {"shoes", 2},
        {"pants", 3},
        {"shirt", 4},
        {"trousers", 5},
        {"belt", 6},
        {"tie", 7},
        {"jacket", 8}
    };
    std::map<int, std::string> ReverseClothes;
    for (const auto& pair : Clothes)
    {
        ReverseClothes[pair.second] = pair.first;
    }

    std::vector<std::vector<int>> objects;
    objects.push_back(std::vector<int>());
    objects.push_back(std::vector<int> {Clothes["shoes"]});
    objects.push_back(std::vector<int>());
    objects.push_back(std::vector<int> {Clothes["shoes"], Clothes["trousers"]});
    objects.push_back(std::vector<int> {Clothes["belt"], Clothes["tie"]});
    objects.push_back(std::vector<int> {Clothes["shoes"], Clothes["belt"]});
    objects.push_back(std::vector<int> {Clothes["jacket"]});
    objects.push_back(std::vector<int> {Clothes["jacket"]});
    objects.push_back(std::vector<int>());
    std::vector<int> sorted = topological_sort(objects);

    for (int i = 0; i < sorted.size(); ++i)
        std::cout << ReverseClothes[sorted[i]] << std::endl;
}