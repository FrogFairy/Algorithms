#include <iostream>
#include <vector>
#include <cmath>


class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) 
    {

        int end_size = nums1.size() + nums2.size(); // размер конечного массива
        if (nums2.size() < nums1.size())
            return findMedianSortedArrays(nums2, nums1);

        int beg = 0, end = nums1.size();
        int min_val = -std::pow(10, 6), max_val = std::pow(10, 6);
        while (true)
        {
            int mid1 = (beg + end) / 2;
            int mid2 = end_size / 2 - mid1; // остаток в первой части конечного массива

            int left1 = (mid1 > 0 ? nums1[mid1 - 1] : min_val);
            int left2 = (mid2 > 0 ? nums2[mid2 - 1] : min_val);
            int right1 = (mid1 < nums1.size() ? nums1[mid1] : max_val);
            int right2 = (mid2 < nums2.size() ? nums2[mid2] : max_val);
            if (left1 <= right2 && left2 <= right1)
            {
                if (end_size % 2 == 0)
                    return (std::max(left1, left2) + std::min(right1, right2)) / 2.0;
                return std::min(right1, right2);
            }
            if (left1 > right2)
                end = mid1 - 1;
            else
                beg = mid1 + 1;
        }
    }
};


int main()
{
    Solution solution;
    std::vector<int> nums1 = {1, 3}, nums2 = {2};
    std::cout << solution.findMedianSortedArrays(nums1, nums2) << std::endl;

    nums1 = {1, 2};
    nums2 = {3, 4};
    std::cout << solution.findMedianSortedArrays(nums1, nums2) << std::endl;

    nums1 = {1, 3, 9, 11, 23, 45, 46};
    nums2 = {2, 4, 6, 7, 8, 21, 22, 23, 44};
    std::cout << solution.findMedianSortedArrays(nums1, nums2) << std::endl;

    nums1 = {1, 2, 3, 5, 6};
    nums2 = {4};
    std::cout << solution.findMedianSortedArrays(nums1, nums2) << std::endl;
}