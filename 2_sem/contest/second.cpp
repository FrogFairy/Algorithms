#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>


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

    int beg = 0, zeros = 0, mx_len = 0, ind_zero = -1;

    for (int i = 0; i < n; ++i)
    {
        if (vec[i] == 0)
            zeros++;
        
        while (zeros > 1)
        {
            if (vec[beg] == 0)
                zeros--;
            beg++;
        }

        if (i - beg + 1 > mx_len)
        {
            mx_len = i - beg + 1;
            ind_zero = (vec[i] == 0 ? i : ind_zero);
        }
    }

    std::cout << ind_zero;
}