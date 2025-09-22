#include <vector>
#include <stack>
#include <iostream>

struct Rectangle
{
    int x;
    int h;

    Rectangle(int x, int h) : x{x}, h{h} {}
};

class Solution 
{
public:
    int trap(std::vector<int>& height) 
    {
        std::stack<Rectangle> st;
        int res = 0;

        for (int i = 0; i < height.size(); ++i)
        {
            Rectangle el(i, height[i]);
            while (!st.empty() && st.top().h <= el.h)
            {
                Rectangle prev = st.top();
                st.pop();
                if (st.empty()) break;
                int distance = i - st.top().x - 1;
                res += distance * (std::min(el.h, st.top().h) - prev.h);
            }
            st.push(el);
        }

        return res;
    }
};

int main()
{
    Solution solution;
    std::vector<int> vec1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::vector<int> vec2 = {4,2,0,3,2,5};
    std::cout << solution.trap(vec1) << std::endl;
    std::cout << solution.trap(vec2) << std::endl;
}