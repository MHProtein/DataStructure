#include <iostream>
#include "BinarySearchTree.h"
#include "MyBinarySearchTree.h"
#include "random"

int main()
{
    BinarySearchTree<int> tree;

    static std::default_random_engine e(time(nullptr));
    for (int i = 0; i != 10; ++i)
    {
        tree.Insert(i);
    }
    tree.PrintTree();
    
    std::cout << tree.FindMax() << std::endl;
    std::cout << tree.FindMin() << std::endl;

    tree.MakeEmpty();
}
