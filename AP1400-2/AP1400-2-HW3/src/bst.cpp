#include "bst.h"

#include <queue>
#include <vector>
#include <memory>

Node::Node()
{
    value = 0;
    left = nullptr;
    right = nullptr;
}

Node::Node(int value, Node* left, Node* right)
    : value(value), left(left), right(right) {}

Node::Node(const Node& node)
{
    value = node.value;
    left = node.left;
    right = node.right;
}

std::ostream& Node::operator<<(std::ostream& os)
{
    os << this << "       => value:" << value
        << "      left:" << left 
        << "      right:" << right;
    return os;
}

bool Node::operator<(int dig)
{
return value < dig;
}

bool Node::operator==(int dig)
{
    return value == dig;
}

bool Node::operator>(int dig)
{
    return value > dig;
}

bool Node::operator<=(int dig)
{
    return value <= dig;
}

bool Node::operator>=(int dig)
{
    return value >= dig;
}

bool operator<(int dig, const Node& node)
{
    return dig < node.value;
}

bool operator>(int dig, const Node& node)
{
    return dig > node.value;
}

bool operator<=(int dig, const Node& node)
{
    return dig <= node.value;
}

bool operator==(int dig, const Node& node)
{
    return dig == node.value;
}

bool operator>=(int dig, const Node& node)
{
    return dig >= node.value;
}

Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func)
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
    while (node != nullptr)
    {
        if (value == (*node).value)
        {
            return false;
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
    node = new Node(value, nullptr, nullptr);
    return true;
}

size_t BST::length()
{
    std::vector<int> values;
    bfs([&values](Node*& node){ values.push_back(node->value); });
    return values.size();
}
