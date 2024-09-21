#include "bst.h"

#include <queue>
#include <vector>

BST::Node::Node()
{
    value = 0;
    left = nullptr;
    right = nullptr;
}

BST::Node::Node(int value, Node *left, Node *right) : value(value), left(left), right(right)
{
}

BST::Node::Node(const Node &node)
{
    value = node.value;
    left = node.left;
    right = node.right;
}

std::ostream &operator<<(std::ostream &os, const BST::Node &node)
{
    os << &node << "       => value:" << node.value << "      left:" << node.left << "      right:" << node.right;
    return os;
}

bool BST::Node::operator<(int dig)
{
    return value < dig;
}

bool BST::Node::operator==(int dig)
{
    return value == dig;
}

bool BST::Node::operator>(int dig)
{
    return value > dig;
}

bool BST::Node::operator<=(int dig)
{
    return value <= dig;
}

bool BST::Node::operator>=(int dig)
{
    return value >= dig;
}

bool operator<(int dig, const BST::Node &node)
{
    return dig < node.value;
}

bool operator>(int dig, const BST::Node &node)
{
    return dig > node.value;
}

bool operator<=(int dig, const BST::Node &node)
{
    return dig <= node.value;
}

bool operator==(int dig, const BST::Node &node)
{
    return dig == node.value;
}

bool operator>=(int dig, const BST::Node &node)
{
    return dig >= node.value;
}

BST::Node *&BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node *&node)> func) const
{
    Node *node;
    std::vector<Node *> serched;
    std::queue<Node *> toSerch;
    if (root == nullptr)
        return;
    toSerch.push(root);
    while (toSerch.size() != 0)
    {
        node = toSerch.front();
        if (std::find(serched.begin(), serched.end(), node) == serched.end())
        {
            serched.push_back(node);
            func(node);
            if (node->left != nullptr)
                toSerch.push(node->left);
            if (node->right != nullptr)
                toSerch.push(node->right);
        }
        toSerch.pop();
    }
}

bool BST::add_node(int value)
{
    if (root == nullptr)
    {
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    Node *node = root;
    int flag = 0;
    while (!flag)
    {
        if (value == (*node).value)
        {
            return false;
        }
        else if (value > (*node).value)
        {
            if (node->right == nullptr)
            {
                flag = 1;
                node->right = new Node(value, nullptr, nullptr);
            }
            node = node->right;
        }
        else
        {
            if (node->left == nullptr)
            {
                node->left = new Node(value, nullptr, nullptr);
                flag = 1;
            }
            node = node->left;
        }
    }

    return true;
}

size_t BST::length() const
{
    std::vector<int> values;
    bfs([&values](Node *&node) { values.push_back(node->value); });
    return values.size();
}

// BST::Node** BST::find_node(int value)
// {
//     Node** nodePtr = nullptr;
//     Node* node = root;
//     while (node != nullptr)
//     {
//         if (value == (*node).value)
//         {
//             nodePtr = &node;
//             std::cout << node << std::endl;
//             std::cout << node->left->value << std::endl;
//             std::cout << (*nodePtr)->left->value << std::endl;
//             std::cout << (*nodePtr)->left <<std::endl;
//             return nodePtr;
//         }
//         else if (value > (*node).value)
//         {
//             node = node->right;
//         }
//         else
//         {
//             node = node->left;
//         }
//     }
//     std::cout << "current*******";
//     return nodePtr;
// }
//
BST::Node **BST::find_node(int value)
{
    Node **nodePtr = &root; // 指向根节点的指针
    while (*nodePtr != nullptr)
    {
        if (value == (*nodePtr)->value) // 找到节点
        {
            return nodePtr;
        }
        else if (value > (*nodePtr)->value)
        {
            nodePtr = &((*nodePtr)->right);
        }
        else
        {
            nodePtr = &((*nodePtr)->left);
        }
    }
    return nullptr;
}

BST::Node **BST::find_parrent(int value)
{
    Node **nodePtr = &root;
    Node **parent = nullptr;
    while (*nodePtr != nullptr)
    {
        if (value == (*nodePtr)->value)
        {
            return parent;
        }
        else if (value > (*nodePtr)->value)
        {
            parent = &(*nodePtr);
            nodePtr = &((*nodePtr)->right);
        }
        else
        {
            parent = &(*nodePtr);
            nodePtr = &((*nodePtr)->left);
        }
    }
    return nullptr;
}

BST::Node **BST::find_successor(int value)
{
    Node **nodePtr = find_node(value);
    if (nodePtr == nullptr)
        return nullptr;
    if ((*nodePtr)->left != nullptr)
    {
        nodePtr = &((*nodePtr)->left);
        while ((*nodePtr)->right != nullptr)
            nodePtr = &((*nodePtr)->right);
        return nodePtr;
    }
    else
    {
        return nullptr;
    }
}

bool BST::delete_node(int value)
{
    Node **parent = find_parrent(value);
    Node **nodePtr = find_node(value);
    Node **successor = find_successor(value);
    if (nodePtr == nullptr)
        return false;
    if (successor == nullptr)
    {
        if ((*nodePtr)->right == nullptr)
        {
            if ((*parent)->value > (*nodePtr)->value)
                (*parent)->right = nullptr;
            else
                (*parent)->left = nullptr;
        }
        else
        {
            if ((*parent)->value > (*nodePtr)->value)
                (*parent)->right = (*nodePtr)->right;
            else
                (*parent)->left = (*nodePtr)->right;
        }
    }
    else
    {
        Node **successorP = find_parrent((*successor)->value);
        if (successorP == nodePtr)
        {
            if ((*parent)->value < (*nodePtr)->value)
            {
                *((*parent)->right) = **successor;
            }
            else
            {
                *((*parent)->left) = **successor;
            }
        }
        else
        {
            if ((*parent)->value < (*nodePtr)->value)
            {
                if ((*nodePtr)->right != nullptr)
                    (*successor)->right = (*nodePtr)->right;
                else
                    (*successor)->right = nullptr;
                *((*parent)->right) = **successor;
            }
            else
            {
                if ((*nodePtr)->left != nullptr)
                    (*successor)->left = (*nodePtr)->left;
                else
                    (*successor)->left = nullptr;
                *((*parent)->left) = **successor;
            }
        }
        if ((*successorP)->value < (*successor)->value)
        {
            (*successorP)->right = nullptr;
        }
        else
        {
            (*successorP)->left = nullptr;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const BST &bst)
{
    BST::Node *node;
    std::vector<BST::Node *> serched;
    std::queue<BST::Node *> toSerch;
    toSerch.push(bst.root);
    std::cout << "current";
    while (toSerch.size() != 0)
    {
        node = toSerch.front();
        if (std::find(serched.begin(), serched.end(), node) == serched.end())
        {
            serched.push_back(node);
            std::cout << *node << std::endl;
            if (node->left != nullptr)
                toSerch.push(node->left);
            if (node->right != nullptr)
                toSerch.push(node->right);
        }
        toSerch.pop();
    }
    os << "binary search tree size: " << bst.length() << std::endl;
    return os;
}

BST BST::operator++()
{

    Node *node;
    std::vector<Node *> serched;
    std::queue<Node *> toSerch;
    toSerch.push(root);
    while (toSerch.size() != 0)
    {
        node = toSerch.front();
        if (std::find(serched.begin(), serched.end(), node) != serched.end())
        {
            serched.push_back(node);
            node->value++;
            if (node->left != nullptr)
                toSerch.push(node->left);
            if (node->right != nullptr)
                toSerch.push(node->right);
        }
        toSerch.pop();
    }
    return *this;
}

BST BST::operator++(int value)
{

    Node *node;
    std::vector<Node *> serched;
    std::queue<Node *> toSerch;
    toSerch.push(root);
    while (toSerch.size() != 0)
    {
        node = toSerch.front();
        if (std::find(serched.begin(), serched.end(), node) != serched.end())
        {
            serched.push_back(node);
            node->value++;
            if (node->left != nullptr)
                toSerch.push(node->left);
            if (node->right != nullptr)
                toSerch.push(node->right);
        }
        toSerch.pop();
    }
    return *this;
}

BST::BST()
{
    root = nullptr;
}

BST::BST(const BST &bst)
{
    std::vector<int> values;
    bst.bfs([&values](Node *&node) { values.push_back(node->value); });
    for (int i = 0; i < values.size(); i++)
    {
        add_node(values[i]);
    }
}

BST::BST(const BST &&bst)
{
    root = bst.root;
}

BST BST::operator=(const BST &bst)
{
    BST newBST;
    std::vector<int> values;
    bst.bfs([&values](Node *&node) { values.push_back(node->value); });
    for (int i = 0; i < values.size(); i++)
    {
        newBST.add_node(values[i]);
    }
    return newBST;
}

BST::BST(const std::initializer_list<int> &il)
{
    for (auto &value : il)
    {
        add_node(value);
    }
}

BST::~BST()
{
    std::vector<Node *> nodes;
    bfs([&nodes](Node *&node) { nodes.push_back(node); });
    std::cout << nodes.size();
    for (auto &node : nodes)
    {
        if (node != nullptr)
            delete node;
    }
}
