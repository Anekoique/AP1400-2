#include "bst.h"

#include <queue>
#include <vector>

BST::Node::Node()
{
    value = 0;
    left = nullptr;
    right = nullptr;
}

BST::Node::Node(int value, Node* left, Node* right)
    : value(value), left(left), right(right) {}

BST::Node::Node(const Node& node)
{
    value = node.value;
    left = node.left;
    right = node.right;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << &node << "       => value:" << node.value
        <<"      left:" << node.left 
        << "      right:" << node.right;
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

bool operator<(int dig, const BST::Node& node)
{
    return dig < node.value;
}

bool operator>(int dig, const BST::Node& node)
{
    return dig > node.value;
}

bool operator<=(int dig, const BST::Node& node)
{
    return dig <= node.value;
}

bool operator==(int dig, const BST::Node& node)
{
    return dig == node.value;
}

bool operator>=(int dig, const BST::Node& node)
{
    return dig >= node.value;
}

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) const
{
    Node * node;
    std::vector<Node*> serched;
    std::queue<Node*> toSerch;
    if (root == nullptr)
        return;
    toSerch.push(root);
    while (toSerch.size() != 0)
    {
        node = toSerch.front();   
        std::cout << node->value << std::endl;
        if (std::find(serched.begin(), serched.end(), node) == serched.end())
        {
            serched.push_back(node);
            func(node);
            if (node->left != nullptr) toSerch.push(node->left);
            if (node->right != nullptr) toSerch.push(node->right);
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
    Node* node = root;
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
    bfs([&values](Node*& node){ values.push_back(node->value); });
    return values.size();
}

BST::Node** BST::find_node(int value)
{
    Node** nodePtr = nullptr;
    Node* node = root;
    while (node != nullptr)
    {
        if (value == (*node).value)
        {
            nodePtr = &node;
            std::cout << node << std::endl;
            std::cout << node->left->value << std::endl;
            std::cout << (*nodePtr)->left->value << std::endl;
            std::cout << (*nodePtr)->left <<std::endl;
            return nodePtr;
        }
        else if (value > (*node).value) 
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }
    return nodePtr;
}

BST::Node** BST::find_parrent(int value)
{
    Node** nodePtr = nullptr;
    Node** parent = nullptr;
    Node* node = root;
    while (node != nullptr)
    {
        if (value == (*node).value)
        {
            nodePtr = parent;
            return nodePtr;
        }
        else if (value > (*node).value)
        {
            parent = &node;
            node = node->right;
        }
        else
        {
            parent = &node;
            node = node->left;
        }
    }
    return nullptr;
}

BST::Node** BST::find_successor(int value)
{
    Node** nodePtr = nullptr;
    Node* node = *find_node(value);
    node = node->left;
    while (node != nullptr)
        node = node->right;
    nodePtr = &node;
    return nodePtr;
}

bool BST::delete_node(int value)
{
    Node* parent = *find_parrent(value);
    Node* node = *find_node(value);
    if (node == nullptr) return false;
    std::vector<int> values;
    bfs([&values](Node*& node){ values.push_back(node->value); });
    values.erase(values.begin());
    if (node->value < parent->value)
    {
        parent->left = nullptr;
    }
    else
    {
        parent->right = nullptr;
    }
    for (int i = 0; i < values.size(); i++) add_node(values[i]);
    return true;
}

std::ostream& operator<<(std::ostream& os, const BST& bst)
{
    BST::Node * node;
    std::vector<BST::Node*> serched;
    std::queue<BST::Node*> toSerch;
    toSerch.push(bst.root);
    while (toSerch.size() != 0)
    {
        node = toSerch.front();   
        if (std::find(serched.begin(), serched.end(), node) != serched.end())
        {
            serched.push_back(node);
            os << node << std::endl;
            if (node->left != nullptr) toSerch.push(node->left);
            if (node->right != nullptr) toSerch.push(node->right);
        }
        toSerch.pop();
    }
    os << "binary search tree size: " << bst.length() << std::endl;
    return os;
}

BST BST::operator++()
{

    Node * node;
    std::vector<Node*> serched;
    std::queue<Node*> toSerch;
    toSerch.push(root);
    while (toSerch.size() != 0)
    {
        node = toSerch.front();   
        if (std::find(serched.begin(), serched.end(), node) != serched.end())
        {
            serched.push_back(node);
            node->value ++;
            if (node->left != nullptr) toSerch.push(node->left);
            if (node->right != nullptr) toSerch.push(node->right);
        }
        toSerch.pop();
    }
    return *this;
}

BST BST::operator++(int value)
{

    Node * node;
    std::vector<Node*> serched;
    std::queue<Node*> toSerch;
    toSerch.push(root);
    while (toSerch.size() != 0)
    {
        node = toSerch.front();   
        if (std::find(serched.begin(), serched.end(), node) != serched.end())
        {
            serched.push_back(node);
            node->value ++;
            if (node->left != nullptr) toSerch.push(node->left);
            if (node->right != nullptr) toSerch.push(node->right);
        }
        toSerch.pop();
    }
    return *this;
}

BST::BST()
{
    root = nullptr;
}

BST::BST(const BST& bst)
{
    std::vector<int> values;
    bst.bfs([&values](Node*& node){ values.push_back(node->value); });
    for (int i = 0; i < values.size(); i++)
    {
        add_node(values[i]);
    }
}

BST::BST(const BST&& bst)
{
    root = bst.root;
}

BST BST::operator=(const BST& bst)
{
    BST newBST;
    std::vector<int> values;
    bst.bfs([&values](Node*& node){ values.push_back(node->value); });
    for (int i = 0; i < values.size(); i++)
    {
        newBST.add_node(values[i]);
    }
    return newBST;
}

BST::BST(const std::initializer_list<int>& il)
{
    for (auto& value : il)
    {
        add_node(value);
    }
}

BST::~BST()
{
    std::vector<Node*> nodes;
    bfs([&nodes](Node*& node){ nodes.push_back(node); });
    std::cout << nodes.size();
    for (auto& node : nodes)
    {
        if (node != nullptr)
            delete node;
    }
}
