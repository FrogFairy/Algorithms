#include <iostream>
#include <vector>


bool with_xor(std::vector<int> vec)
{
    int res = 0 ^ vec[0];
    for (int i = 1; i < vec.size(); ++i)
    {
        res ^= vec[i] ^ i;
    }
    return res;
}


bool without_xor(std::vector<int> vec)
{
    int res = 0;
    for (int el: vec)
    {
        res += el;
    }
    return res != (vec.size() - 1) * vec.size() / 2;
}


int main()
{
    std::vector<int> a = {1, 2, 3, 4, 1};
    std::cout << with_xor(a) << std::endl;
    std::cout << without_xor(a) << std::endl;
}