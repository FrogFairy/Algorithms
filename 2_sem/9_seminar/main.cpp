#include <vector>
#include <iostream>
#include <algorithm>

bool compare_string(std::string& s1, std::string& s2)
{
    if (s1.size() < s2.size())
        return true;
    for (int i = 0; i < std::min(s1.size(), s2.size()); ++i)
    {
        if (s1[i] < s2[i])
            return true;
        if (s1[i] > s2[i])
            return false;
    }
    return false;
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
    std::cin >> n;
    std::vector<std::string> vec;
    for (int i = 0; i < n; ++i)
    {
        std::string val;
        std::cin >> val;
        vec.push_back(val);
    }

    std::sort(vec.begin(), vec.end(), compare_string);
    
    std::cout << vec;
}