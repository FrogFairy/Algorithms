#include <iostream>
#include <vector>
#include <unordered_map>

int solution(std::vector<int>& vec1, std::vector<int>& vec2)
{
    std::unordered_map<int, int> first;
    first[0] = -1;
    int result = 0;
    int x = 0, y = 0;
    for (int i = 0; i < vec1.size(); ++i)
    {
        x += vec1[i];
        y += vec2[i];
        
        if (first.find(x - y) != first.end())
            result = std::max(result, i - first[x - y]);
        else
            first[x - y] = i;
    }
    return result;
}


int main()
{
    int n;
    std::cin >> n;
    std::vector<int> vec1, vec2;
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        vec1.push_back(val);
    }

    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        vec2.push_back(val);
    }

    std::cout << solution(vec1, vec2) << std::endl;
}