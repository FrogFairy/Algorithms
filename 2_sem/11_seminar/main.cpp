#include <iostream>
#include <vector>

struct TreeNode
{
    int key = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

void tree_insert(TreeNode *&n, int key)
{
    if (n == nullptr)
        n = new TreeNode{key};
    else if (n->key < key)
        tree_insert(n->right, key);
    else if (n->key > key)
        tree_insert(n->left, key);
}

int tree_height(TreeNode *n)
{
    if (n == nullptr)
        return 0;
    return std::max(tree_height(n->left), tree_height(n->right)) + 1;
}

bool is_balanced(TreeNode *n)
{
    if (n == nullptr)
        return true;
    
    if (std::abs(tree_height(n->left) - tree_height(n->right)) <= 1)
        return is_balanced(n->left) && is_balanced(n->right);
    return false;
}

// bool is_binary_tree(TreeNode *n, int key)
// {
//     if (n == nullptr)
//         return true;
    
//     if ((n->left && n->key > n->left->key || !n->left) &&
//         (n->right && n->key < n->right->key || !n->right))
//         return is_binary_tree(n->left) && is_binary_tree(n->right);
//     return false;
// }

bool tree_contains(TreeNode *n, int key)
{
    if (n == nullptr)
        return false;
    if (n->key < key)
        return tree_contains(n->right, key);
    else if (n->key > key)
        return tree_contains(n->left, key);
    return true;
}

void tree_remove(TreeNode *&n, int key)
{
    if (n == nullptr)
        return;
    if (n->key < key)
        return tree_remove(n->right, key);
    else if (n->key > key)
        return tree_remove(n->left, key);
    else if(n->right == nullptr)
    {
        TreeNode* x = n;
        n = n->left;
        delete x;
    }
    else if (n->left == nulltr)
    {
        TreeNode* x = n;
        n = n->right;
        delete x;
    }
    else
    {
        TreeNode* x = n->right;
        TreeNode* p = n;
        while (x->left != nullptr)
        {
            p = x;
            x = x->left;
        }
        n->key = x->key;
        (x == p->left ? p->left : p->right) = x->right;
        delete x;
    }
}

std::ostream& operator<<(std::ostream &os, TreeNode *n)
{
    if (n == nullptr)
        return os;
    os << n->left;
    os << n->key << " ";
    os << n->right;
    return os;
}

int main()
{
    TreeNode *root = nullptr;
    for (int key : {8, 3, 6, 1, 2, 8, 9})
        tree_insert(root, key);
    std::cout << root << std::endl;
    std::cout << is_balanced(root) << std::endl;
}

/*
     7
    / \
    6     9
   /    /  \
   3   8    10  
  /
  2
 /
 1   
*/