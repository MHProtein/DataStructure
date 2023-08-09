#include <iostream>
#include "BinarySearchTree.h"
#include "MyBinarySearchTree.h"
#include "AVLTree.h"
#include "random"

int main()
{
    AVLTree<int> tree;

    static std::default_random_engine e(time(nullptr));
    for (int i = 0; i != 10; ++i)
    {
        tree.Insert(i);
    }
    AVLTree<int> tree2 = tree;
    tree.Remove(5);
    tree2.PrintTree();
    
    std::cout << tree2.FindMax() << std::endl;
    std::cout << tree2.FindMin() << std::endl;

    tree.MakeEmpty();
}
