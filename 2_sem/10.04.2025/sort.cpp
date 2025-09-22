#include <vector>
#include <iostream>

class Solution
{
public:
    void heapify(std::vector<int>& nums, int n, int i)
    {
        int parent = i;
        int ind_child1 = 2 * i + 1;
        int ind_child2 = 2 * i + 2;

        if (ind_child1 < n && nums[ind_child1] > nums[parent])
            parent = ind_child1;
        
        if (ind_child2 < n && nums[ind_child2] > nums[parent])
            parent = ind_child2;
        
        if (i != parent)
        {
            std::swap(nums[i], nums[parent]);
            heapify(nums, n, parent);
        }
    }

    std::vector<int> sortArray(std::vector<int>& nums)
    {
        // проходим по элементам, начиная от последнего родительского (строим кучу)
        for (int i = nums.size() / 2 - 1; i >= 0; --i)
            heapify(nums, nums.size(), i);
        
        // перемещаем максимальный элемент в куче (первый) в конец
        // и сортируем кучу для нового первого элемента
        for (int i = nums.size() - 1; i > 0; --i)
        {
            std::swap(nums[i], nums[0]);
            heapify(nums, i, 0); 
        }
        return nums;
    }
};

std::ostream& operator<< (std::ostream& os, std::vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";
    return os;
}


int main()
{
    Solution solution;

    std::vector<int> nums {5, 2, 3, 1};
    nums = solution.sortArray(nums);
    std::cout << nums << std::endl;

    nums = {5, 1, 1, 2, 0, 0};
    nums = solution.sortArray(nums);
    std::cout << nums << std::endl;
}