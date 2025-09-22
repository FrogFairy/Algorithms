#include <iostream>
#include <vector>
#include <unordered_map>
#include "algorithm"

std::vector<int> solution(std::vector<int>& vec1, std::vector<int>& vec2)
{
    std::vector<int> result;
    std::unordered_map<int, int> count;
    for (int num : vec1)
        count[num]++;
    
    for (int num : vec2)
    {
        if (count.count(num))
        {
            for (int i = 0; i < count[num]; ++i)
                result.push_back(num);
            count.erase(num);
        }
    }

    std::vector<std::pair<int, int>> vec(count.begin(), count.end());
    std::sort(vec.begin(), vec.end(), [](const std::pair<int, int> a, const std::pair<int, int> b)
                                            {
                                                return a.first < b.first;
                                            });


    for (const auto& pair : vec)
    {
        for (int i = 0; i < pair.second; ++i)
            result.push_back(pair.first);
    }

    return result;
}

std::ostream& operator<< (std::ostream& os, std::vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";
    return os;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> vec1, vec2;
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        vec1.push_back(val);
    }

    for (int i = 0; i < m; ++i)
    {
        int val;
        std::cin >> val;
        vec2.push_back(val);
    }

    std::vector<int> result = solution(vec1, vec2);

    std::cout << result << std::endl;
}