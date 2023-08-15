#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#pragma once
#include <algorithm>
#include <iostream>
#include <ostream>

template <class Type>
class BinarySearchTree
{
public:
    BinarySearchTree()
    {
        root_ = nullptr;
    }

    BinarySearchTree(const BinarySearchTree& bst)
    {
        root_ = clone(bst.root_);
    }

    BinarySearchTree(BinarySearchTree&& bst) noexcept : root_(std::move(bst.root_))
    {
        bst.root_ = nullptr;
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
        BinarySearchTree temp(rhs);
        std::swap(*this, temp);
        return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept
    {
        std::swap(root_, rhs.root_);
        return *this;
    }

    ~BinarySearchTree()
    {
        if (!IsEmpty())
            MakeEmpty();
    }

    const Type& FindMax() const
    {
        return FindMax(root_)->data_;
    }

    const Type& FindMin() const
    {
        return FindMin(root_)->data_;
    }

    void MakeEmpty()
    {
        if (!IsEmpty())
            makeEmpty(root_);
    }

    bool IsEmpty() const { return root_ == nullptr; }

    void Insert(const Type& item)
    {
        Insert(item, root_);
    }

    void Insert(Type&& item)
    {
        Insert(std::forward<Type&&>(item), root_);
    }

    void Remove(const Type& item)
    {
        Remove(item, root_);
    }

    bool Contain(const Type& item) const
    {
        return Contain(item, root_);
    }

    void PrintTree(std::ostream& out = std::cout)
    {
        PrintTree(out, root_, "", false);
    }

private:
    struct BinaryNode
    {
        BinaryNode(const Type& Data, BinaryNode* Left, BinaryNode* Right): data_(Data), left_(Left), right_(Right)
        {
        }

        BinaryNode(Type&& Data, BinaryNode* Left, BinaryNode* Right) noexcept : data_(Data), left_(Left), right_(Right)
        {
        }

        Type data_;
        BinaryNode* left_;
        BinaryNode* right_;
    };

    BinaryNode* root_;

    BinaryNode* clone(BinaryNode* t)
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        return new BinaryNode(t->data_, clone(t->left_), clone(t->right_));
    }

    void makeEmpty(BinaryNode*& t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left_);
            makeEmpty(t->right_);
            delete t;
        }
        t = nullptr;
    }

    BinaryNode* FindMax(BinaryNode* t) const
    {
        if(t == nullptr)
            return nullptr;
        while(t->right_ != nullptr)
        {
            t = t->right_;
        }
        return t;
    }

    BinaryNode* FindMin(BinaryNode* t) const
    {
        if(t == nullptr)
            return nullptr;
        while(t->left_ != nullptr)
        {
            t = t->left_;
        }
        return t;
    }

    void Insert(const Type& item, BinaryNode*& t)
    {
        if (t == nullptr)
            t = new BinaryNode(item, nullptr, nullptr);
        if (item < t->data_)
            Insert(item, t->left_);
        if (t->data_ < item)
            Insert(item, t->right_);
    }

    void Insert(Type&& item, BinaryNode*& t)
    {
        if (t == nullptr)
            t = new BinaryNode(std::move(item), nullptr, nullptr);
        if (item < t->data_)
            Insert(std::forward<Type&&>(item), t->left_);
        if (t->data_ < item)
            Insert(std::forward<Type&&>(item), t->right_);
    }

    void Remove(const Type& item, BinaryNode*& t)
    {
        if (IsEmpty())
            return;
        
        if (item < t->data_)
            Remove(item, t->left_);
        else if (t->data_ < item)
            Remove(item, t->right_);
        else if (t->left_ != nullptr && t->right_ != nullptr)
        {
            t->data_ = FindMin(t->right_)->data_;
            Remove(t->data_, t->right_);
        }
        else
        {
            BinaryNode* OldNode = t;
            t = (t->left_ != nullptr) ? t->left_ : t->right_;
            delete OldNode;
        }
    }

    bool Contain(const Type& item, BinaryNode*& t)
    {
        if (t == nullptr)
            return false;
        if (item < t->data_)
        {
            return Contain(item, t->left_);
        }
        if (t->data_ < item)
        {
            return Contain(item, t->right_);
        }
        return true;
    }

    void PrintTree(std::ostream& out, BinaryNode* t, std::string prefix, bool IsLeft)
    {
        if (t != nullptr)
        {
            out << prefix;
            out << (IsLeft ? u8"├──" : u8"└──");
            out << t->data_ << std::endl;
            PrintTree(out, t->left_, prefix + (IsLeft ? u8"│  " : u8"   "), true);
            PrintTree(out, t->right_, prefix + (IsLeft ? u8"│  " : u8"   "), false);
        }
    }
};
#endif
