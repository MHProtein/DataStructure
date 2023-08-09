#pragma once
#include <algorithm>
#include <iostream>
#include <ostream>

template<class Type>
class AVLTree
{
    static const int ALLOWED_IMBALANCE = 1;
public:
    AVLTree()
    {
        root_ = nullptr;
    }

    AVLTree(const AVLTree& avl)
    {
        root_ = Clone(avl.root_);
    }

    AVLTree(AVLTree&& avl) noexcept : root_(std::move(avl.root_))
    {
        avl.root_ = nullptr;
    }

    AVLTree& operator=(const AVLTree& rhs)
    {
        AVLTree temp(rhs);
        std::swap(*this,temp);
        return *this;
    }

    AVLTree& operator=(AVLTree&& rhs) noexcept
    {
        std::swap(root_, rhs.root_);
        return *this;
    }

    ~AVLTree()
    {
        MakeEmpty();
    }

    void MakeEmpty()
    {
        MakeEmpty(root_);
    }

    bool IsEmpty() const
    {
        return root_ == nullptr;
    }

    bool Contain(const Type& item) const
    {
        return Contain(item, root_);
    }

    Type& FindMax() const
    {
        return FindMax(root_)->element;
    }

    Type& FindMin() const
    {
        return FindMin(root_)->element;
    }

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

    void PrintTree(std::ostream& out = std::cout)
    {
        PrintTree(out, root_, "", false);
    }

private:
    
    struct AVLNode
    {
        AVLNode(const Type& Element, AVLNode* Left, AVLNode* Right, int Height = 0): element(Element), left(Left), right(Right), height(Height){ }
        AVLNode(Type&& Element, AVLNode* Left, AVLNode* Right, int Height = 0) noexcept : element(std::move(Element)), left(Left), right(Right), height(Height){ }

        Type element;
        AVLNode* left;
        AVLNode* right;
        int height;
    };

    AVLNode* root_;

    int Height(AVLNode* t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    AVLNode* Clone(AVLNode* t)
    {
        if(t == nullptr)
            return nullptr;
        return new AVLNode(t->element, Clone(t->left), Clone(t->right));
    }

    void MakeEmpty(AVLNode*& t)
    {
        if(t != nullptr)
        {
            MakeEmpty(t->left);
            MakeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    bool Contain(const Type& item, AVLNode* t) const
    {
        if(t == nullptr)
        {
            return false;
        }
        if(item < t->element)
        {
            return Contain(t->left);
        }
        if(item < t->element)
        {
            return Contain(t->right);
        }
        return true;
    }

    AVLNode* FindMax(AVLNode* t) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        if(t->right == nullptr)
        {
            return t;
        }
        return FindMax(t->right);
    }

    AVLNode* FindMin(AVLNode* t) const
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        if(t->left == nullptr)
        {
            return t;
        }
        return FindMin(t->left);
    }

    void Insert(const Type& item, AVLNode*& t)
    {
        if(t == nullptr)
        {
            t = new AVLNode(item, nullptr, nullptr);
        }
        if(item < t->element)
        {
            Insert(item, t->left);
        }
        else if(t->element < item)
        {
            Insert(item, t->right);
        }
        Balance(t);
    }

    void Insert(Type&& item, AVLNode*& t)
    {
        if(t == nullptr)
        {
            t = new AVLNode(std::move(item), nullptr, nullptr);
        }
        if(item < t->element)
        {
            Insert(std::forward<Type&&>(item), t->left);
        }
        else if(t->element < item)
        {
            Insert(std::forward<Type&&>(item), t->right);
        }
        Balance(t);
    }

    void Remove(const Type& item, AVLNode*& t)
    {
        if(t == nullptr)
            return;
        if(item < t->element)
        {
            Remove(item,t->left);
        }
        else if(t->element < item)
        {
            Remove(item, t->right);
        }
        else if(t->left != nullptr && t->right != nullptr)
        {
            t->element = FindMax(t->right)->element;
            Remove(t->element, t->right);
        }
        else
        {
            AVLNode* OldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete OldNode;
        }
        Balance(t);
    }

    void Balance(AVLNode*& t)
    {
        if(t == nullptr)
            return;
        if(Height(t->left) - Height(t->right) > ALLOWED_IMBALANCE)
            if(Height(t->left->left) >= Height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        else if(Height(t->right) - Height(t->left) > ALLOWED_IMBALANCE)
            if(Height(t->right->right) >= Height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        t->height = std::max(Height(t->left), Height(t->right)) + 1;
    }

    void rotateWithLeftChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(Height(k2->left), Height(k2->right)) + 1;
        k1->height = std::max(Height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = std::max(Height(k2->left), Height(k2->right)) + 1;
        k1->height = std::max(k2->height, Height(k1->right)) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild(AVLNode*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AVLNode*& k3)
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    void PrintTree(std::ostream& out, AVLNode* t, const std::string& prefix, bool isLeft)
    {
        if(t == nullptr)
            return;
        
        out << prefix;
        out << (isLeft ? u8"├──" : u8"└──");
        out << t->element << std::endl;

        PrintTree(out, t->left, prefix + (isLeft ? u8"│  " : "   "), true);
        PrintTree(out, t->right, prefix + (isLeft ? u8"│  " : "   "), false);
    }
};
