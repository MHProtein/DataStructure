#include <iostream>
#include "BinarySearchTree.h"
#include "MyBinarySearchTree.h"
#include "AVLTree.h"
#include "random"

int main()
{
    AVLTree<int> tree;

    static std::default_random_engine e(time(nullptr));

    tree.Insert(3);
    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(16);
    tree.Insert(15);
    tree.Insert(14);
    tree.Insert(13);
    tree.Insert(12);
    tree.Insert(11);
    tree.Insert(10);
    tree.Insert(8);
    tree.Insert(9);
    tree.PrintTree();
    AVLTree<int> tree2 = tree;
    tree.Remove(5);

    

    tree.MakeEmpty();
}
