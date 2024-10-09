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

// void BST::bfs(std::function<void(Node *&node)> func) const
// {
//     Node *node;
//     std::vector<Node *> serched;
//     std::queue<Node *> toSerch;
//     if (root == nullptr)
//         return;
//     toSerch.push(root);
//     while (toSerch.size() != 0)
//     {
//         node = toSerch.front();
//         if (std::find(serched.begin(), serched.end(), node) == serched.end())
//         {
//             serched.push_back(node);
//             func(node);
//             if (node->left != nullptr)
//                 toSerch.push(node->left);
//             if (node->right != nullptr)
//                 toSerch.push(node->right);
//         }
//         toSerch.pop();
//     }
// }

void BST::bfs(std::function<void(Node *&node)> func) const
{
    std::queue<Node *> toSerch;
    Node* current = root;
    if (current == nullptr) return;
    toSerch.push(current);
    while (!toSerch.empty())
    {
        current = toSerch.front();
        func(current);
        toSerch.pop();
        if (current->left) toSerch.push(current->left);
        if (current->right) toSerch.push(current->right);
    }
}

bool BST::add_node(int value)
{
    //if (root == nullptr)
    //{
    //    root = new Node(value, nullptr, nullptr);
    //    return true;
    //}
    //Node *node = root;
    //int flag = 0;
    //while (!flag)
    //{
    //    if (value == (*node).value)
    //    {
    //        return false;
    //    }
    //    else if (value > (*node).value)
    //    {
    //        if (node->right == nullptr)
    //        {
    //            flag = 1;
    //            node->right = new Node(value, nullptr, nullptr);
    //        }
    //        node = node->right;
    //    }
    //    else
    //    {
    //        if (node->left == nullptr)
    //        {
    //            node->left = new Node(value, nullptr, nullptr);
    //            flag = 1;
    //        }
    //        node = node->left;
    //    }
    //}

    //return true;
    Node *node = new Node(value, nullptr, nullptr);
    if (get_root() == nullptr) {
        root = node;
        return true;
    }
    Node *curr = get_root();
    Node *prev;
    while (curr != nullptr) {
        if (*curr == value) { // 运算符重载
            return false;
        } else if (value > *curr) {
            prev = curr;
            curr = curr->right;
        } else if (value < *curr) {
            prev = curr;
            curr = curr->left;
        }
    }
    if (value > *prev) {
        prev->right = node;
    } else if (value < *prev) {
        prev->left = node;
    }
    return true;
}

// 递归实现添加节点
bool BST::add_node(int value, Node* current)
{
    if (current == nullptr)
    {
        current = new Node(value, nullptr, nullptr);
        return true;
    }

    if (value < current->value)
        return add_node(value, current->left);
    else if (value == current->value)
        return false;
    else 
        return add_node(value, current->right);
}

size_t BST::length() const
{
    std::vector<int> values;
    bfs([&values](Node *&node) { values.push_back(node->value); });
    return values.size();
}

// 递归求树的长度
size_t BST::length(Node* current)
{
    size_t len;
    if(current == nullptr) return 0;
    len = 1 + length(current->left) + length(current->right);
    return len;
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
        if (value == **nodePtr) // 找到节点
        {
            return nodePtr;
        }
        else if (value > **nodePtr)
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
    Node** nodePtr = find_node(value);
    Node** parent = find_parrent(value);
    if (nodePtr == nullptr) return false;
    if ((*nodePtr)->right == nullptr)
    {
        if ((*nodePtr)->left != nullptr)
        {
            if ((*parent)->value > (*nodePtr)->value)
            {
                (*parent)->left = (*nodePtr)->left;
            }
            else
            {
                (*parent)->right = (*nodePtr)->left;
            }
        }
        else
        {
            if ((*parent)->value > (*nodePtr)->value)
            {
                (*parent)->left = nullptr;
            }
            else
            {
                (*parent)->right = nullptr;
            }
        }
    }
    else if ((*nodePtr)->left == nullptr)
    {
        if ((*nodePtr)->right != nullptr)
        {
            if ((*parent)->value > (*nodePtr)->value)
            {
                (*parent)->left = (*nodePtr)->right;
            }
            else
            {
                (*parent)->right = (*nodePtr)->right;
            }
        }
        else
        {
            if ((*parent)->value > (*nodePtr)->value)
            {
                (*parent)->left = nullptr;
            }
            else
            {
                (*parent)->right = nullptr;
            }
        }
    }
    else
    {
        if (parent != nullptr)
        {
            Node** successor = find_successor(value);
            std::cout << (*successor)->value << std::endl;
            Node** successorP = find_parrent((*successor)->value);
            std::cout << (*successorP)->value << std::endl;
            (*successor)->left = (*nodePtr)->left;
            (*successor)->right = (*nodePtr)->right;
            if ((*parent)->value > (*nodePtr)->value)
            {
                (*parent)->left = (*successorP)->right;
            }
            else
            {
                (*parent)->right = (*successorP)->right;
            }
            (*successorP)->right = nullptr;
        }
        else
        {
            Node** successor = find_successor(value);
            std::cout << (*successor)->value << std::endl;
            Node** successorP = find_parrent((*successor)->value);
            std::cout << (*successorP)->value << std::endl;
            (*successor)->left = (*nodePtr)->left;
            (*successor)->right = (*nodePtr)->right;
            root = (*successorP)->right;
            (*successorP)->right = nullptr;

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

// BST BST::operator++()
// {
//     Node *node;
//     std::vector<Node *> serched;
//     std::queue<Node *> toSerch;
//     toSerch.push(root);
//     while (toSerch.size() != 0)
//     {
//         node = toSerch.front();
//         if (std::find(serched.begin(), serched.end(), node) == serched.end())
//         {
//             serched.push_back(node);
//             node->value += 1;
//             if (node->left != nullptr)
//                 toSerch.push(node->left);
//             if (node->right != nullptr)
//                 toSerch.push(node->right);
//         }
//         toSerch.pop();
//     }
//     return *this;
// }

// BST BST::operator++(int value)
// {
//     BST temp = *this;
//     std::cout << "current" << std::endl;
//     Node *node;
//     std::vector<Node *> serched;
//     std::queue<Node *> toSerch;
//     toSerch.push(root);
//     while (toSerch.size() != 0)
//     {
//         node = toSerch.front();
//         if (std::find(serched.begin(), serched.end(), node) == serched.end())
//         {
//             serched.push_back(node);
//             std::cout << "node:value" << node->value << std::endl;
//             node->value += 1;
//             std::cout << "node:value" << node->value << std::endl;
//             if (node->left != nullptr)
//                 toSerch.push(node->left);
//             if (node->right != nullptr)
//                 toSerch.push(node->right);
//         }
//         toSerch.pop();
//     }
//     std::cout << *this;
//     return temp;
// }

BST& BST::operator++()
{
    std::vector<Node *> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (Node* node : nodes)
    {
        node->value ++;
    }
    return *this;
}

BST BST::operator++(int)
{
    auto copy = (*this);
    ++(*this);
    return copy;
}

BST::BST()
{
    root = nullptr;
}

BST::BST(const BST &bst) : BST()
{
    std::vector<int> values;
    bst.bfs([&values](Node *&node) { values.push_back(node->value); });
    for (int i = 0; i < values.size(); i++)
    {
        this->add_node(values[i]);
    }
}

BST::BST(BST &&bst)
{
    root = bst.root;
    bst.root = nullptr;
}

BST& BST::operator=(const BST &bst)
{
    if (bst.root == this->root) {
        return *this;
    }
    this->~BST(); // 先释放原本的树的内存

    std::vector<int> values;
    bst.bfs([&values](Node *&node) { values.push_back(node->value); });
    for (int i = 0; i < values.size(); i++)
    {
        add_node(values[i]);
    }

    return *this;
}

BST& BST::operator=(BST&& bst)
{
    this->~BST(); // 先释放原本的树的内存
    root = bst.root;
    bst.root = nullptr;
    return *this;

}

BST::BST(const std::initializer_list<int> &il)
{
    root = nullptr;
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
        delete node;
    }
}
