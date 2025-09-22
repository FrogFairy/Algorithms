#include <iostream>
#include <vector>

bool check_max_jump(int n, int k, std::string s, int max_jump)
{
    int prev = -1, next = -1;
    for (int i = 0; i < s.size(); ++i)
    {
        if (k == 0)
            return false;
        if (s[i] == '1')
        {
            if (i - prev < max_jump)
            {
                next = i;
            }
            else
            {
                if (i - prev == max_jump)
                    next = i;
                prev = next;
                --k;
            }
        }
    }
    if (prev != next)
    {
        prev = next;
        --k;
    }
    return k >= 1 && (n - 1 - prev) <= max_jump;
}

int get_max_jump(int n, int k, std::string s)
{
    int beg = 1, end = n;
    while (beg < end)
    {
        int mid = (beg + end) / 2; // максимальная длина прыжка
        if (check_max_jump(n, k, s, mid))
            end = mid;
        else
            beg = mid + 1;
    }
    return beg;
}


int main()
{
    std::cout << get_max_jump(10, 2, "001001000") << std::endl;
    std::cout << get_max_jump(5, 5, "0000") << std::endl;
}