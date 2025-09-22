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

    int n;
    std::cin >> n;
    std::vector<int> vec {};
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        vec.push_back(val);
    }

    std::cout << solution.trap(vec) << std::endl;
}