#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

struct Rectangle
{
    Rectangle(int x1, int x2, int height)
    : x1{x1}, x2{x2}, height{height} {}

    int x1;
    int x2;
    int height;
};

int solution(std::vector<Rectangle>& vec)
{
    int res = 0;
    std::stack<Rectangle> st;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (st.empty() || st.top().height < vec[i].height)
        {
            st.push(vec[i]);
        }
        else
        {
            Rectangle top = st.top();
            st.pop();
            while (!st.empty() && st.top().height >= vec[i].height)
            {
                res = std::max(res, (top.x2 - st.top().x1) * st.top().height);
                st.push(Rectangle(st.top().x1, top.x2, st.top().height));
                top = st.top();
                st.pop();
            }
            res = std::max(res, (top.x2 - vec[i].x1) * vec[i].height);
            st.push(vec[i]);
        }
    }

    while (!st.empty())
    {
        Rectangle top = st.top();
        st.pop();
        res = std::max(res, (top.x2 - (st.empty() ? 0 : st.top().x1)) * top.height);
    }

    return res;
}

struct Queue
{
    void push(int val)
    {
        st.push(val);
    }

    void pop()
    {
        if (st.empty()) return;
        std::stack<int> buff;
        while(!st.empty())
        {
            buff.push(st.top());
            st.pop();
        }
        buff.pop();
        while (!buff.empty())
        {
            st.push(buff.top());
            buff.pop();
        }
    }

    int front()
    {
        if (st.empty()) return;
        std::stack<int> buff;
        while(!st.empty())
        {
            buff.push(st.top());
            st.pop();
        }
        return buff.top();
    }

private:
    std::stack<int> st;
}

int main()
{
    std::vector<std::vector<int>> a = {{30, 30}, {10, 40}, {20, 10}, {10, 40}};
    std::vector<Rectangle> b {};
    int start = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        b.push_back(Rectangle(start, start + a[i][0], a[i][1]));
        start += a[i][0];
    }
    std::cout << solution(b) << std::endl;
    return 0;
}