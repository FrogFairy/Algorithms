#include <vector>
#include <iostream>
#include <algorithm>

std::vector<std::string> solution(std::vector<std::vector<std::string>>& vec, 
                                    std::vector<int>& priorities)
{
    std::sort(vec.begin(), vec.end(), 
            [&priorities](std::vector<std::string> left, std::vector<std::string> right)
                {
                    for (int i = 0; i < priorities.size(); ++i)
                    {
                        int left_val = std::stoi(left[priorities[i]]);
                        int right_val = std::stoi(right[priorities[i]]);
                        if (left_val > right_val)
                            return true;
                        if (left_val < right_val)
                            return false;
                    }
                    return false;
                }
            );
    
    std::vector<std::string> res;
    for (int i = 0; i < vec.size(); ++i)
        res.push_back(vec[i][0]);
    return res;
}

std::ostream& operator<< (std::ostream& os, std::vector<std::string>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i] << std::endl;
    return os;
}

int main()
{
    int n;
    int k;

    std::cin >> n >> k;

    std::vector<int> priorities;
    std::vector<std::vector<std::string>> vec;

    for (int i = 0; i < k; ++i)
    {
        int val;
        std::cin >> val;
        priorities.push_back(val);
    }

    for (int i = 0; i < n; ++i)
    {
        std::vector<std::string> line;
        for (int j = 0; j < k + 1; ++j)
        {
            std::string el;
            std::cin >> el;
            line.push_back(el);
        }
        vec.push_back(line);
    }

    std::vector<std::string> sol = solution(vec, priorities);
    std::cout << sol;
}