#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    using std::cout;
    using std::endl;
    if (true) // make false to run unit-tests
    {
        // debug section
        BST bst{};
        bst.add_node(25);
        bst.add_node(10);
        bst.add_node(50);
        bst.add_node(65);
        bst.add_node(60);
        bst.add_node(70);
        bst.add_node(5);
        bst.add_node(2);
        bst.add_node(7);
        bst.add_node(75); 
        cout << bst;
        bst.delete_node(10);
        cout << bst;
        
//        cout << bst.length() << endl;
//        cout << bst.length() << endl;
//        EXPECT_EQ(bst.length(), 8);
//        EXPECT_TRUE(bst.delete_node(53)); // leaf node
//        EXPECT_EQ(bst.length(), 7);
//        EXPECT_EQ(bst.get_root()->right->right, nullptr); 
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
