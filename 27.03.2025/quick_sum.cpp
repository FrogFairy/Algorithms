#include "heap.h"

int solution(std::vector<int>& values)
{
    if (values.empty()) return 0;

    Heap heap;
    for (int el: values)
    {
        heap.push(-el);
    }
    int res = 0;
    int s = 0;
    while (!heap.empty())
    {
        s = -heap.pop();
        if (heap.empty())
            break;
        s += -heap.pop();
        res += s;
        heap.push(-s);
    }
    return res;
}

int main()
{
    std::vector<int> vec {5, 2, 3, 4, 6};
    std::cout << solution(vec) << std::endl;
    vec = {3, 7, 6, 1, 9};
    std::cout << solution(vec) << std::endl;
}