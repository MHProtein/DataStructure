#include <iostream>
#include "BinarySearchTree.h"
#include "random"

int main()
{
    BinarySearchTree<int> tree;

    static std::default_random_engine e(time(nullptr));
    for (int i = 0; i != 10; ++i)
    {
        tree.Insert(e() % 10);
    }
    tree.PrintTree();
    std::cout << tree.IsEmpty() << std::endl;
    std::cout << tree.FindMax() << std::endl;
    std::cout << tree.FindMin() << std::endl;

    tree.MakeEmpty();
}
