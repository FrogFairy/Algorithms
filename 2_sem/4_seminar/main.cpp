#include <iostream>
#include <vector>


void solution(std::vector<int>& vec)
{
    int k = 0;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] >= 0)
        {
            vec[k] = vec[i];
            k++;
        }
    }
    vec.resize(k);
}

struct ListNode
{
    int data;
    ListNode *prev = nullptr;
    ListNode *next = nullptr;
};

struct List
{
    ListNode *front = nullptr;
    ListNode *back = nullptr;

    ~List()
    {
        ListNode* n = front;
        while (n)
        {
            ListNode* a = n;
            n = n->next;
            delete a;
        }
    }

    void push_back(int val)
    {
        if (back == nullptr)
        {
            back = new ListNode{val};
            front = back;
        }
        else
        {
            ListNode *n = new ListNode{val};
            back->next = n;
            n->prev = back;
            back = n;
        }
    }

    void pop_back(int val)
    {
        ListNode* n = back;
        back = n->prev;
        if (back)
            back->next = nullptr;
        delete n;
    }

    void push_front(int val)
    {
        if (front == nullptr)
        {
            front = new ListNode{val};
            back = front;
        }
        else
        {
            ListNode* n = new ListNode{val};
            front->prev = n;
            n->next = front;
            front = n;
        }
    }

    void pop_front(int val)
    {
        ListNode* n = front;
        front = n->next;
        if (front)
        front->prev = nullptr;
        delete n;
    }

    void insert(ListNode* n, int val)
    {
        if (n == nullptr)
        {
            push_back(val);
            return;
        }
        if (n->prev && n->next)
        {
            ListNode *n1 = new ListNode{val, n->prev, n};
            n->prev->next = n1;
            n->prev = n1;
        }
    }

    void remove(ListNode* n)
    {
        if (n == nullptr)
            return;
        if (n->prev)
        {
            n->prev->next = n->next;
            if (n->next == nullptr)
                back = n->prev;
        }
        if (n->next)
        {
            n->next->prev = n->prev;
            if (n->prev == nullptr)
                front = n->next;
        }
        delete n;
    }
};

int main()
{
    std::vector<int> a = {3, -2, 1, -1, 0, 4, 5, -3};
    solution(a);
    for (int i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << std::endl;
    }

    List a;
    ListNode n1{1}, n2{2}, n3{3};
    a.push_back(n1);
    a.push_back(n2);
    a.push_back(n3);
    a.remove(n1);
    a.remove(n2);
    a.remove(n3);
}