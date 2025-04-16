#include <iostream>
#include <vector>
#include "inttypes.h"
#include <sstream>

int64_t merge(std::vector<int>& vec, int64_t beg_left, int64_t beg_right, int64_t end_right)
{
    int64_t i = beg_left, j = beg_right;
    int64_t result = 0;
    std::vector<int> new_vec;
    while (i < beg_right && j < end_right)
    {
        if (vec[i] <= vec[j])
        {
            new_vec.push_back(vec[i]);
            ++i;
        }
        else
        {
            new_vec.push_back(vec[j]);
            result += beg_right - i;
            ++j;
        }
    }
    new_vec.insert(new_vec.end(), vec.begin() + i, vec.begin() + beg_right);
    new_vec.insert(new_vec.end(), vec.begin() + j, vec.begin() + end_right);
    std::copy(new_vec.begin(), new_vec.end(), vec.begin() + beg_left);
    return result;
}

int64_t solution(std::vector<int>& vec, int64_t beg, int64_t end)
{
    int64_t size = end - beg;
    if (size <= 1)
        return 0;
    
    int64_t mid = (beg + end) / 2;
    int64_t inv_left = solution(vec, beg, mid);
    int64_t inv_right = solution(vec, mid, end);
    int64_t inv_merge = merge(vec, beg, mid, end);
    return inv_left + inv_right + inv_merge;
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::stringstream stream(line);

    std::vector<int> vec;
    int val;
    while (stream >> val)
        vec.push_back(val);
    
    std::cout << solution(vec, 0, vec.size());
}