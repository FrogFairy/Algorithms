#include <vector>

std::vector<std::vector<int>> matrix_to_list(std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<int>> res;
    for (int i = 0; i < matrix.size(); ++i)
    {
        std::vector<int> arr;
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j] == 1)
                arr.push_back(j);
        }
        res.push_back(arr);
    }
    
    return res;
}

std::vector<std::vector<int>> list_to_matrix(std::vector<std::vector<int>>& list)
{
    int s = list.size();
    std::vector<std::vector<int>> res(s, std::vector<int>(s, 0));
    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; i < s; ++j)
        {
            res[i][j] = 1;
        }
    }

    return res;
}