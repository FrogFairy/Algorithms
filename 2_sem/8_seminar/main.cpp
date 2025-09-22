#include <iostream>
#include <vector>
#include <algorithm>

// [b, e)
int partition(std::vector<int> &a, int b, int e)
{
    std::swap(a[b + (e - b) / 2], a[e - 1]);
    int i = b;
    int j = e - 2;
    while(i <= j)
    {
        while (a[i] < a[e - 1])
            ++i;
        while (j > 0 && a[j] >= a[e - 1])
            --j;
        if (i < j)
            std::swap(a[i++], a[j--]);
        else
            break;
    }
    std::swap(a[i], a[e - 1]);
    return i;
}

void quick_sort(std::vector<int> &a, int b, int e)
{
    if (b < e)
    {
        int p = partition(a, b, e);
        quick_sort(a, b, p);
        quick_sort(a, p + 1, e);
    }
}

int find_k_elem(std::vector<int> &a, int k, int b, int e)
{
    int p = partition(a, b, e);
    if (p == k)
        return a[k];
    if (p < k)
        return find_k_elem(a, k, p + 1, e);
    return find_k_elem(a, k, b, p);
}

struct Box
{
    int id;
    int w, l, h;
};


std::ostream& operator<<(std::ostream& os, std::vector<int>& a)
{
    for (int value : a)
        os << value << " ";
    os << std::endl;
    return os;
}

int main()
{
    // std::vector<int> a = {6, 2, 1, 3, 4, 8, 7, 5};
    // std::cout << find_k_elem(a, 3, 0, a.size()) << std::endl;
    // quick_sort(a, 0, a.size());
    // std::cout << a << std::endl;
    // int n;
    // std::cin >> n;
    // std::vector<Box> boxes;
    // for (int i = 0; i <= n; ++i)
    // {
    //     int wlh[3];
    //     std::cin >> wlh[0] >> wlh[1] >> wlh[2];
    //     std::sort(wlh, wlh + 3);
    //     boxes.push_back(Box{i, wlh[0], wlh[1], wlh[2]});
    //     delete[] wlh;
    // }

    // std::sort(boxes.begin(), boxes.end(), [](Box b0, Box b1)
    //             {
    //                 if (b0.w == b1.w)
    //                 {
    //                     if (b0.l == b1.l)
    //                         return b0.h < b1.h;
    //                     return b0.l < b1.l;
    //                 }
    //                 return b0.w < b1.w;
    //             });
    
    // for (int i = 0; i < n; ++i)
    //     std::cout << boxes[i].id << " ";

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> points;
    for (int i = 0; i < n; ++i)
    {
        
    }
}