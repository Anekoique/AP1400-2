#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        // debug section
        BST bst{};
        bst.add_node(25);
        bst.add_node(10);
        bst.add_node(50);
        bst.add_node(53);
        bst.add_node(15);
        bst.add_node(7);
        
        BST::Node** node{bst.find_node(10)}; 
        std::cout << *node << std::endl;
        std::cout << (*node)->value << std::endl;
        std::cout << (*node)->left << std::endl;
        std::cout << (*node)->left->value << std::endl;
        std::cout << (*node)->right->value << std::endl;
       //if (bst.get_root() == nullptr) std::cout << "right";
 
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}
