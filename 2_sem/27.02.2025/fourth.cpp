#include <vector>
#include <iostream>
#include <cmath>


std::vector<int> get_index(std::vector<int> a, std::vector<int> b)
{
    std::vector<int> res;
    for (int el : b)
    {
        bool flag = false;

        int beg = 1;
        while (a[beg] < el)
            beg *= 2;
        int end = std::min(size_t(beg + 1), a.size());
        beg /= 2;
        while (beg < end)
        {
            int mid = (beg + end) / 2;
            if (a[mid] >= el)
            {
                if (mid == 0 || a[mid - 1] < el)
                {
                    flag = true;
                    res.push_back(mid);
                    break;
                }
                end = mid;
            }
            if (a[mid] < el)
                beg = mid + 1;
        }
        if (!flag)
            res.push_back(a.size());
    }
    return res;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& a)
{
    os << "[";
    for (int i = 0; i < a.size(); ++i)
    {
        os << a[i];
        if (i < a.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}


int main()
{
    std::vector<int> a = {10, 20, 50};
    std::vector<int> b = {1, 15, 38, 51};
    std::cout << get_index(a, b) << std::endl;
}