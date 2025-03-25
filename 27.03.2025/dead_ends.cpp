#include "heap.h"
#include <bits/stdc++.h>

int solution(std::vector<std::pair<int, int>> values)
{
    Heap heap;
    for (std::pair<int, int> el: values)
    {
        if (!heap.empty())
        {
            int last = heap.pop();
            if (el.first <= -last)
                heap.push(-last);
        }
        heap.push(-el.second);
    }
    return heap.size();
}

int main()
{
    std::vector<std::pair<int, int>> vec1 {std::pair<int, int> {10, 20}};
    std::vector<std::pair<int, int>> vec2 {std::pair<int, int> {10, 20}, std::pair<int, int> {20, 25}};
    std::vector<std::pair<int, int>> vec3 {std::pair<int, int> {10, 20}, std::pair<int, int> {20, 25}, std::pair<int, int> {21, 30}};
    std::cout << solution(vec1) << std::endl;
    std::cout << solution(vec2) << std::endl;
    std::cout << solution(vec3) << std::endl;
}