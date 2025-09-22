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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) 
    {
        ListNode* start = nullptr;
        ListNode* current = nullptr;        

        while (list1 || list2)
        {
            if (list1 && (!list2 || list2 && list1->val <= list2->val))
            {
                if (!start)
                {
                    start = new ListNode(list1->val);
                    current = start;
                }
                else
                {
                    current->next = list1;
                    current = current->next;
                }
                list1 = list1->next;
            }
            else
            {
                if (!start)
                {
                    start = new ListNode(list2->val);
                    current = start;
                }
                else
                {
                    current->next = list2;
                    current = current->next;
                }
                list2 = list2->next;
            }
        }
        return start;
    }
};


int main()
{
    Solution solution;
    ListNode* list1 = nullptr;

    ListNode* list2 = new ListNode();

    ListNode* list = solution.mergeTwoLists(list1, list2);
    while (list)
    {
        std::cout << list->val << " ";
        list = list->next;
    }
}