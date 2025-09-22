#include <iostream>
#include <vector>

int solution(int n, std::vector<int>& vec)
{
    for (int i = 0; i < n; ++i)
    {
        if (vec[i] <= 0)
            vec[i] = n + 1;
    }

    for (int i = 0; i < n; ++i)
    {
        int val = std::abs(vec[i]);
        if (val < n + 1)
        {
            vec[val - 1] = -std::abs(vec[val - 1]);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (vec[i] > 0)
            return i + 1;
    }

    return n + 1;
}


int main()
{
    int n;
    std::cin >> n;
    std::vector<int> vec;
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        vec.push_back(val);
    }

    std::cout << solution(n, vec) << std::endl;
}