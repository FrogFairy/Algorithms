#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>

struct MyStr
{
    std::string val;
    MyStr(std::string val) : val{val} {}
};

bool operator<(MyStr s1, MyStr s2)
{
    return s1.val + s2.val < s2.val + s1.val;
}

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

    std::vector<MyStr> res {};
    std::make_heap(res.begin(), res.end());

    for (int i = 0; i < n; ++i)
    {
        res.push_back(MyStr(std::to_string(vec[i])));
        std::push_heap(res.begin(), res.end());
    }

    while (!res.empty())
    {
        std::string val = res[0].val;
        std::pop_heap(res.begin(), res.end());
        res.pop_back();
        std::cout << val;
    }
}