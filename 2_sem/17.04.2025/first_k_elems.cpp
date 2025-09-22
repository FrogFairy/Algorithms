#include <iostream>
#include <vector>
#include <bits/stdc++.h>

void add_elem(std::vector<int>& heap, int elem, int k)
{
    if (heap.size() < k)
    {
        heap.push_back(elem);
        std::push_heap(heap.begin(), heap.end());
    }
    else if (elem < heap[0])
    {
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();

        heap.push_back(elem);
        std::push_heap(heap.begin(), heap.end());
    }
}

std::ostream& operator<< (std::ostream& os, std::vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";
    return os;
}

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> result;
    std::make_heap(result.begin(), result.end());
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        add_elem(result, val, k);
    }

    std::sort(result.begin(), result.end());
    std::cout << result << std::endl;
}