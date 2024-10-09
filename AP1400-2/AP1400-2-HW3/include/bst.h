#ifndef BST_H
#define BST_H

#include <functional>
#include <iostream>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);
        
        bool operator<(int dig);
        bool operator>(int dig);
        bool operator<=(int dig);
        bool operator>=(int dig);
        bool operator==(int dig);

        friend std::ostream& operator<<(std::ostream& os, const Node& node);
        friend bool operator<(int dig, const Node& node);
        friend bool operator>(int dig, const Node& node);
        friend bool operator<=(int dig, const Node& node);
        friend bool operator>=(int dig, const Node& node);
        friend bool operator==(int dig, const Node& node);
        
        int value;
        Node* left;
        Node* right;
    };

    BST();
    BST(const BST& bst);
    BST(BST&& bst);
    BST(const std::initializer_list<int>& il);
    ~BST();
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    size_t length(Node* current);
    bool add_node(int value);
    bool add_node(int value, Node* current);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, const BST& bst);
    BST& operator++();
    BST operator++(int value);
    BST& operator=(const BST& bst);
    BST& operator=(BST&& bst);

private:
    Node* root;
};
#endif //BST_H
