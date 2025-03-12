#include <iostream>


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
        ListNode* start = nullptr;
        ListNode* double_prev = nullptr;
        ListNode* prev = nullptr;
        ListNode* current = nullptr;

        while (head)
        {
            double_prev = prev;
            prev = current;
            if (!start)
            {
                start = new ListNode(head->val);
                current = start;
            }
            if (prev)
            {
                if (head->val == prev->val)
                {
                    while (head->val == prev->val)
                    {
                        head = head->next;
                        if (!head) break;
                    }
                    prev = double_prev;
                    if (prev)
                        prev->next = nullptr;
                    current = prev;
                    if (!prev)
                    {
                        start = nullptr;
                        continue;
                    }
                    if (!head) break;
                }
                if (head->val != prev->val)
                {
                    current = new ListNode(head->val);
                    prev->next = current;
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