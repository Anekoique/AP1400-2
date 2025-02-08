#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    using std::cout;
    using std::endl;
    if (false) // make false to run unit-tests
    {
        // debug section
        BST bst{5, 1, 10, 2, 8, 50, 4, 60};
        BST bst2{++bst}; 
        BST bst3{bst++};
        std::cout << bst;
        std::cout << bst2;
        std::cout << bst3;
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
