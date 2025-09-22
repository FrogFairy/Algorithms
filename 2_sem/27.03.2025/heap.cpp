#include "heap.h"

void Heap::sift_up(int ind)
{
    int parent = (ind - 1) / 2;
    if (ind == 0 || vec[parent] >= vec[ind])
        return;
    int buff = vec[parent];
    vec[parent] = vec[ind];
    vec[ind] = buff;
    sift_up(parent);
}

void Heap::sift_down(int ind)
{
    int child_1 = ind * 2 + 1, child_2 = ind * 2 + 2;
    if (ind >= vec.size() - 1 || child_1 >= vec.size() && child_2 >= vec.size() || 
        child_1 < vec.size() && vec[child_1] <= vec[ind] || child_2 < vec.size() && vec[child_2] <= vec[ind])
        return;
    int new_ind, buff;
    if (child_1 < vec.size() && vec[child_1] > vec[child_2])
    {
        buff = vec[child_1];
        vec[child_1] = vec[ind];
        new_ind = child_1;
    }
    else
    {
        buff = vec[child_2];
        vec[child_2] = vec[ind];
        new_ind = child_2;
    }
    vec[ind] = buff;
    sift_down(new_ind);
}