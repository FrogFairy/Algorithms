#include <bits/stdc++.h>
#include <iostream>

std::vector<int> solution(std::vector<int> vec, int k)
{
    std::vector<int> res;

    std::vector<std::pair<int, int>> heap {};
    std::make_heap(heap.begin(), heap.end());
    for (int i = 0; i < vec.size(); ++i)
    {
        heap.push_back(std::pair<int, int>{vec[i], i});
        std::push_heap(heap.begin(), heap.end());
        if (i >= k - 1)
        {
            std::pair<int, int> last = heap[0];
            while (last.second <= i - k)
            {
                std::pop_heap(heap.begin(), heap.end());
                heap.pop_back();
                last = heap[0];
            }
            res.push_back(last.first);
        }
    }

    return res;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
    for (int el : vec)
    {
        os << el << " ";
    }
    return os;
}

int main()
{
    std::vector<int> vec1 {1, 2, 3};
    std::vector<int> vec2 {0, 7, 3, 8, 4, 5, 10, 4, 6};
    std::vector<int> res1 = solution(vec1, 2);
    std::vector<int> res2 = solution(vec2, 4);
    std::cout << res1 << std::endl;
    std::cout << res2 << std::endl;
}