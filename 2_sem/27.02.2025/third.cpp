#include <iostream>
#include <vector>

// не смогла придумать решение задачи без редактирования массива.

int get_replay(std::vector<int> vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[std::abs(vec[i])] < 0) // нашли элемент, который уже заменяли
        {
            return std::abs(vec[i]);
        }
        vec[std::abs(vec[i])] *= (-1);
    }
}


// без редактирования массива можно вывести, есть ли 
// повторы в последовательности (с помощью XOR или с помощью формулы для
// суммы арифметической прогресии)
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
    std::vector<int> a = {1, 2, 3, 4, 2, 1};
    std::cout << get_replay(a) << std::endl;
    std::cout << with_xor(a) << std::endl;
    std::cout << without_xor(a) << std::endl;

    std::vector<int> b = {1, 2, 4, 5, 6, 1, 0, 3};
    std::cout << get_replay(b) << std::endl;
    std::cout << with_xor(b) << std::endl;
    std::cout << without_xor(b) << std::endl;
}