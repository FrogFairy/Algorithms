#include <iostream>
#include <vector>
#include <cmath>


// int solution_1(const std::vector<int>& vec)
// {
//     int end = 1;
//     while (end < vec.size() || vec[end - 1] < vec[end])
//     {
//         end *= 2;
//     }
//     int beg = end / 2;
//     if (end >= vec.size()) end = vec.size() - 1;
//     int mid = (beg + end) / 2;
//     while(beg < end)
//     {
//         mid = (beg + end) / 2;
//         // if (vec[mid - 1] < vec[mid] && vec[mid] > vec[mid + 1])
//         //     return mid;
//         if (vec[mid] < vec[mid + 1])
//             beg = mid + 1;
//         else if (vec[mid] > vec[mid + 1])
//             end = mid;
//         else
//             return mid;
//     }
//     // return mid - 1;
//     return beg;
// }

// int solution_2(const std::vector<int>& a, const std::vector<int>& b)
// {
//     for (int val: b)
//     {
//         int end = 1;
//         while (a[end] <= val)
//         {
//             end *= 2;
//         }
//         int beg = end / 2;
//         while (beg < end)
//         {
//             int mid = (beg + end) / 2;
//             if (vec[mid] == val)
//                 return mid;
//             if (vec[mid] < val)
//                 beg = mid + 1;
//             else
//                 end = mid;
//         }
//         if (std::abs(vec[end] - val) < std::abs(vec[beg] - val))
//             return end;
//         return beg;
//     }
// }


struct House
{
public:
    House(std::vector<std::vector<int>> flats) : flats{flats} {};

    int get_floor(int flat)
    {
        int beg = 0, end = flats.size();
        while (beg < end)
        {
            int mid = (beg + end) / 2;
            if (flats[mid][0] <= flat && flat <= flats[mid][1])
                return mid + 1;
            if (flats[mid][1] < flat)
                beg = mid + 1;
            else
                end = mid;
        }
        return -1;
    }

private:
    std::vector<std::vector<int>> flats;
};


int main()
{
    // std::vector<int> arr = {1, 2, 3, 6, -9, -10, -11};
    // std::cout << solution(arr) << std::endl;

    std::vector<std::vector<int>> flats = {{0, 1}, {2, 4}, {5, 15}};
    House house(flats);
    std::cout << house.get_floor(16) << std::endl;
}