#include <iostream>
#include <vector>
#include "inttypes.h"
#include <sstream>

void merge(std::vector<int>& vec, std::vector<int>& count, int beg_left, int beg_right, int end_right)
{
    int i = beg_left, j = beg_right;
    std::vector<std::pair<int, int>> new_vec;
    while (i < beg_right && j < end_right)
    {
        if (vec[i].first <= vec[j].first)
        {
            new_vec.push_back(vec[i]);
            ++i;
        }
        else
        {
            new_vec.push_back(vec[j]);
            count[vec[j].second] += beg_right - i;
            ++j;
        }
    }
    new_vec.insert(new_vec.end(), vec.begin() + i, vec.begin() + beg_right);
    new_vec.insert(new_vec.end(), vec.begin() + j, vec.begin() + end_right);
    std::copy(new_vec.begin(), new_vec.end(), vec.begin() + beg_left);
}

void solution(std::vector<std::pair<int, int>>& vec, std::vector<int>& count, int beg, int end)
{
    int size = end - beg;
    if (size <= 1)
        return;
    
    int mid = (beg + end) / 2;
    solution(vec, beg, mid);
    solution(vec, mid, end);
    merge(vec, beg, mid, end);
}

vector<int> count_inversions(vector<int>& vec) {
    int n = vec.size();
    std::vector<std::pair<int, int>> nums;
    std::vector<int> counts(n, 0);
    
    for (int i = 0; i < n; ++i) {
        nums.push_back(vec[i], i);
    }
    
    solution(nums, counts, 0, n);
    return counts;
}

std::ostream& operator<< (std::ostream& os, std::vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";
    return os;
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
    std::vector<int> res = count_inversions(vec);

    std::cout << res << std::endl;
}