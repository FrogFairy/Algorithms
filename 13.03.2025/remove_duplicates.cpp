#include <iostream>
#include <stack>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        std::stack<ListNode*> st;
        ListNode* start = nullptr;

        while (head)
        {
            if (st.empty())
            {
                st.push(new ListNode(head->val));
                start = st.top();
            }
            else
            {
                if (head->val == st.top()->val)
                {
                    while (head->val == st.top()->val)
                    {
                        head = head->next;
                        if (!head) break;
                    }
                    st.pop();
                    if (!st.empty())
                        st.top()->next = nullptr;
                    else
                    {
                        start = nullptr;
                        continue;
                    }
                    if (!head) break;
                }
                if (head->val != st.top()->val)
                {
                    ListNode* cur = new ListNode(head->val);
                    st.top()->next = cur;
                    st.push(cur);
                }
            }
            head = head->next;
        }
        
        return start;
    }
};


int main()
{
    Solution solution;
    ListNode* list = new ListNode(1);
    list->next = new ListNode(1);
    list->next->next = new ListNode(1);

    ListNode* res = solution.deleteDuplicates(list);
    while (res)
    {
        std::cout << res->val << " ";
        res = res->next;
    }
}