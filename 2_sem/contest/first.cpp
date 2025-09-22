#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> vec {};
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        vec.push_back(val);
    }

    std::sort(vec.begin(), vec.end());
    if (vec.size() < 3)
        std::cout << "No triplet exists" << std::endl;
    else
    {
        int val1 = vec[0] * vec[1] * vec[2];
        int val2 = vec[0] * vec[vec.size() - 2] * vec[vec.size() - 1];
        if (val1 < val2)
            std::cout << val1 << std::endl;
        else
            std::cout << val2 << std::endl;
    }
}