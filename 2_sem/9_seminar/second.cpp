#include <vector>
#include <iostream>
#include <algorithm>

struct Line
{
    int begin;
    int end;
};

bool operator<(Line& l1, Line& l2)
{
    if (l1.begin == l2.begin)
        return l1.end < l2.end;
    return l1.begin < l2.begin;
}

int solution(std::vector<Line>& vec)
{
    std::sort(vec.begin(), vec.end());
    std::vector<Line> lines = {vec[0]};
    int i = 1;
    while (i < vec.size())
    {
        Line last = lines[lines.size() - 1];
        if (vec[i].begin <= last.end)
        {
            lines.pop_back();
            lines.push_back(Line{last.begin, vec[i].end});
        }
        else
            lines.push_back(vec[i]);
        i++;
    }
    
    int length = 0;
    for (int i = 0; i < lines.size(); ++i)
    {
        length += lines[i].end - lines[i].begin;
    }
    return length;
}

int main()
{
    int n = 1;
    std::vector<Line> vec = {Line{1, 4}, Line{7, 8}, Line{2, 5}};
    std::cout << solution(vec) << std::endl;
}