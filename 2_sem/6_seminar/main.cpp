#include <vector>
#include <iostream>

struct Heap
{
    std::vector<int> vec;
    Heap() : vec{} {}
    void sift_up(int ind)
    {
        int parent = (ind - 1) % 2;
        if (ind == 0 || vec[parent] >= vec[ind])
            return;
        int buff = vec[parent];
        vec[parent] = vec[ind];
        vec[ind] = buff;
        sift_up(parent);
    }

    void sift_down(int ind)
    {
        int child_1 = ind * 2 + 1, child_2 = ind * 2 + 2;
        if (ind == vec.size() - 1 || vec[child_1] <= vec[ind] && vec[child_2] <= vec[ind])
            return;
        int buff = std::max(vec[child_1], vec[child_2]);
        int new_ind;
        if (vec[child_1] > vec[child_2])
        {
            vec[child_1] = vec[ind];
            new_ind = child_1;
        }
        else
        {
            vec[child_2] = vec[ind];
            new_ind = child_2;
        }
        vec[ind] = buff;
        sift_down(new_ind);
    }

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
};

// std::vector<int> solution(std::vector<int> values, int k)
// {
//     Heap heap;
//     std::vector<int> res;
//     for (int i = 0; i < k; ++i)
//         heap.push(values[i]);
//     for (int i = k; i < values.size(); ++i)
//     {
//         res.push_back(heap.pop());
//         heap.push(values[i]);
//     }
//     res.push_back(heap.pop());
//     return res;
// }

int solution(std::vector<int> values, int k)
{
    Heap heap;
    for (int i = 0; i < values.size(); ++i)
        heap.push(values[i]);
        
    int res = 0;
    while (!heap.empty())
    {
        std::vector<int> cur;
        int cur_sum = 0;
        while (!heap.empty() && cur_sum < k)
        {
            int last = heap.pop();
            if (cur_sum + last > k)
            {
                heap.push(last);
                break;
            }
            cur_sum += last;
            cur.push_back(last);
        }
        for (int i = 0; i < cur.size(); ++i)
        {
            if (cur[i] > 1)
                heap.push(cur[i] / 2);
        }
        ++res;
    }
    return res;
}

int main()
{
    int n = 7;
    std::vector<int> vec = {1, 1, 1, 1, 1, 1, 1};
    int k = 3;
    int res = solution(vec, k);
    std::cout << res << std::endl;
}