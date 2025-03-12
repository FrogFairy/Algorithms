#include <stack>
#include <string>
#include <algorithm>
#include <iostream>

class Solution {
public:
    std::string simplifyPath(std::string path) 
    {
        std::stack<char> st;
        int point_count = 0;
        for (char el : path + '/')
        {
            if (el == '/')
            {
                if (point_count == 1)
                    st.pop();
                else if (point_count == 2)
                {
                    st.pop(); // первая точка
                    st.pop(); // вторая точка
                    if (st.size() >= 2)
                    {
                        st.pop(); // слэш
                        while (st.top() != '/')
                            st.pop();
                    }
                    
                }
                else if (st.empty() || st.top() != '/')
                    st.push(el);
                point_count = 0;
            }
            else if ((st.top() == '/' || point_count != 0) && el == '.')
            {
                point_count++;
                st.push(el);
            }
            else
            {
                point_count = 0;
                st.push(el);
            }
        }
        if (st.size() > 1 && st.top() == '/')
            st.pop();

        std::string res;
        while (!st.empty())
        {
            res += st.top();
            st.pop();
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
};


int main()
{
    std::string s1 = "/home/";
    std::string s2 = "/home//foo/";
    std::string s3 = "/home/user/Documents/../Pictures";
    std::string s4 = "/../";
    std::string s5 = "/.../a/../b/c/../d/./";
    std::string s6 = "/a//b////c/d//././/..";
    Solution solution;
    // std::cout << solution.simplifyPath(s1) << std::endl;
    // std::cout << solution.simplifyPath(s2) << std::endl;
    // std::cout << solution.simplifyPath(s3) << std::endl;
    // std::cout << solution.simplifyPath(s4) << std::endl;
    // std::cout << solution.simplifyPath(s5) << std::endl;
    std::cout << solution.simplifyPath(s6) << std::endl;
}