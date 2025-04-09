#include <vector>
#include <iostream>
#include <algorithm>

void solution(std::vector<std::pair<int, int>>& vec)
{
    std::sort(vec.begin(), vec.end(), 
                [](std::pair<int, int> left, std::pair<int, int> right) -> bool 
                {
                    return left.first < right.first || 
                    (left.first == right.first && left.second < right.second);
                }
            );
}

std::ostream& operator<< (std::ostream& os, std::vector<std::pair<int, int>>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i].first << " " << vec[i].second << std::endl;
    return os;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> vec;
    for (int i = 0; i < n; ++i)
    {
        std::pair<int, int> point;
        std::cin >> point.first >> point.second;
        vec.push_back(point);
    }

    solution(vec);
    std::cout << vec;
}