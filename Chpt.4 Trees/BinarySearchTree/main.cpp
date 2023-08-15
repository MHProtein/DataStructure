#include <iostream>
#include "BinarySearchTree.h"
#include "MyBinarySearchTree.h"
#include "AVLTree.h"
#include "random"
#include <fstream>
#include <map>
#include <set>
#include "ThreadedBinaryTree.h"

int main()
{
    AVLTree<int> tree;
    static std::default_random_engine e(time(nullptr));

    for(int i = 0; i != 2; ++i)
    {
        tree.Insert(i);
    }

    std::cout << clock() << std::endl;

    std::fstream f("D:/output.txt", std::_Iosb<int>::app);
    // tree.Insert(3);
    // tree.Insert(2);
    // tree.Insert(1);
    // tree.Insert(4);
    // tree.Insert(5);
    // tree.Insert(6);
    // tree.Insert(7);
    // tree.Insert(16);
    // tree.Insert(15);
    // tree.Insert(14);
    // tree.Insert(13);
    // tree.Insert(12);
    // tree.Insert(11);
    // tree.Insert(10);
    // tree.Insert(8);
    // tree.Insert(9);
    //
    AVLTree<int> tree2 = tree;
    tree2.PrintTree();
    tree2.PrintTreeInorder();
    tree.MakeEmpty();
    
    for(int i = 0; i != 10; ++i)
    {
        tree.Insert(i);
    }
}
