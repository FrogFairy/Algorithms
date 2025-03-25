#ifndef HEAP
#define HEAP

#include <vector>
#include <iostream>

struct Heap
{
    std::vector<int> vec;
    Heap() : vec{} {}
    void sift_up(int ind);

    void sift_down(int ind);

    void push(int val)
    {
        vec.push_back(val);
        sift_up(vec.size() - 1);
    }

    int pop()
    {
        int res = vec[0];
        vec[0] = vec[vec.size() - 1];
        vec.pop_back();
        sift_down(0);
        return res;
    }

    bool empty() { return vec.empty(); }
    int size() { return vec.size(); }
};

#endif // HEAP