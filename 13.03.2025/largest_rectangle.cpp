#include <vector>
#include <stack>
#include <iostream>

struct Rectangle
{
    int x1;
    int x2;
    int h;

    Rectangle(int x1, int x2, int h) : x1{x1}, x2{x2}, h{h} {}
};

class Solution 
{
public:
    int largestRectangleArea(std::vector<int>& heights) 
    {
        std::stack<Rectangle> st;
        int res = 0;
        for (int i = 0; i < heights.size(); ++i)
        {
            Rectangle el(i, i + 1, heights[i]);

            if (!st.empty() && st.top().h > el.h)
            {
                Rectangle top = st.top();
                res = std::max(res, (top.x2 - top.x1) * top.h);
                st.pop();
                while (!st.empty() && st.top().h > el.h)
                {
                    res = std::max(res, (top.x2 - st.top().x1) * st.top().h);
                    Rectangle new_rec(st.top().x1, top.x2, st.top().h);
                    st.pop();
                    st.push(new_rec);
                    top = st.top();
                    st.pop();
                }
                if (top.h >= el.h)
                    st.push(Rectangle(top.x1, el.x2, el.h));
                else
                    st.push(el);
            }
            
            else
                st.push(el);
            res = std::max(res, el.h);
        }

        while (!st.empty())
        {
            Rectangle top = st.top();
            res = std::max(res, (top.x2 - top.x1) * top.h);
            st.pop();
            if (st.empty()) break;
            res = std::max(res, (top.x2 - st.top().x1) * st.top().h);
            Rectangle new_rec(st.top().x1, top.x2, st.top().h);
            st.pop();
            st.push(new_rec);
        }

        return res;
    }
};

int main()
{
    Solution solution;
    std::vector<int> vec1 = {2,1,5,6,2,3};
    std::vector<int> vec2 = {2, 4};
    std::vector<int> vec3 = {5, 4, 1, 2};
    // std::cout << solution.largestRectangleArea(vec1) << std::endl;
    // std::cout << solution.largestRectangleArea(vec2) << std::endl;
    std::cout << solution.largestRectangleArea(vec3) << std::endl;
}