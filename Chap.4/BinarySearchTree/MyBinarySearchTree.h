#pragma once
#include <iostream>
#include <ostream>

template <typename Comparable>
class MyBinarySearchTree
{
public:
    MyBinarySearchTree();
    MyBinarySearchTree(const MyBinarySearchTree& rhs);
    MyBinarySearchTree(MyBinarySearchTree&& rhs) noexcept;
    ~MyBinarySearchTree();

    const Comparable& findMin() const;
    const Comparable& findMax() const;
    bool contains(const Comparable& x) const;
    bool isEmpty() const;
    void printTree(std::ostream& out = std::cout) const;

    void makeEmpty();
    void insert(const Comparable& x);
    void insert(Comparable&& x);
    void remove(const Comparable& x);

    MyBinarySearchTree& operator=(const MyBinarySearchTree& rhs);
    MyBinarySearchTree& operator=(MyBinarySearchTree&& rhs) noexcept;

private:
    struct BinaryNode
    {
        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt): element_(theElement), left_(lt),
            right_(rt)
        {
        }

        BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt) noexcept : element_(theElement), left_(lt),
            right_(rt)
        {
        }

        Comparable element_;
        BinaryNode* left_;
        BinaryNode* right_;
    };

    BinaryNode* root_;

    void insert(const Comparable& x, BinaryNode*& t);
    void insert(Comparable&& x, BinaryNode*& t);
    void remove(const Comparable& x, BinaryNode*& t);
    BinaryNode* findMin(BinaryNode* t) const;
    BinaryNode* findMax(BinaryNode* t) const;
    bool contains(const Comparable& x, BinaryNode* t) const;
    void makeEmpty(BinaryNode*& t);
    void printTree(BinaryNode* t, std::ostream& out, std::string prefix, bool isLeft) const;
    BinaryNode* clone(BinaryNode* t) const;
};

template <typename Comparable>
MyBinarySearchTree<Comparable>::MyBinarySearchTree()
{
    root_ = nullptr;
}

template <typename Comparable>
MyBinarySearchTree<Comparable>::MyBinarySearchTree(const MyBinarySearchTree& rhs)
{
    root_ = clone(rhs.root_);
}

template <typename Comparable>
MyBinarySearchTree<Comparable>::MyBinarySearchTree(MyBinarySearchTree&& rhs) noexcept : root_(std::move(rhs.root_))
{
    rhs.root_ = nullptr;
}

template <typename Comparable>
MyBinarySearchTree<Comparable>::~MyBinarySearchTree()
{
    makeEmpty();
}

template <typename Comparable>
const Comparable& MyBinarySearchTree<Comparable>::findMin() const
{
    return findMin(root_)->element_;
}

template <typename Comparable>
const Comparable& MyBinarySearchTree<Comparable>::findMax() const
{
    return findMax(root_)->element_;
}

template <typename Comparable>
bool MyBinarySearchTree<Comparable>::contains(const Comparable& x) const
{
    return contains(x, root_);
}

template <typename Comparable>
bool MyBinarySearchTree<Comparable>::isEmpty() const
{
    return root_ == nullptr;
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::printTree(std::ostream& out) const
{
    if (isEmpty())
    {
        out << "Empty Tree!" << std::endl;
    }
    printTree(root_, out, "", true);
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::makeEmpty()
{
    makeEmpty(root_);
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::insert(const Comparable& x)
{
    insert(x, root_);
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::insert(Comparable&& x)
{
    insert(std::forward<Comparable&&>(x), root_);
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::remove(const Comparable& x)
{
    remove(x, root_);
}

template <typename Comparable>
MyBinarySearchTree<Comparable>& MyBinarySearchTree<Comparable>::operator=(const MyBinarySearchTree& rhs)
{
    MyBinarySearchTree temp = rhs;
    std::swap(*this, temp);
    return *this;
}

template <typename Comparable>
MyBinarySearchTree<Comparable>& MyBinarySearchTree<Comparable>::operator=(MyBinarySearchTree&& rhs) noexcept
{
    std::swap(this->root_, rhs.root_);
    return *this;
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode*& t)
{
    if (t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
    else if (x < t->element_)
        insert(x, t->left_);
    else if (t->element_ < x)
        insert(x, t->right_);
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::insert(Comparable&& x, BinaryNode*& t)
{
    if (t == nullptr)
        t = new BinaryNode(std::move(x), nullptr, nullptr);
    else if (x < t->element_)
        insert(std::forward<Comparable&&>(x), t->left_);
    else if (t->element_ < x)
        insert(std::forward<Comparable&&>(x), t->right_);
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode*& t)
{
    if (isEmpty())
        return;
    
    if (x < t->element_)
        remove(x, t->left_);
    else if (t->element_ < x)
        remove(x, t->right_);
    else if (t->right_ != nullptr && t->left_ != nullptr) //two children
    {
        t->element_ = findMin(t->right_)->element_;
        remove(t->element_, t->right_);
    }
    else
    {
        BinaryNode* ToBeDel = t;
        t = (t->left_ != nullptr) ? t->left_ : t->right_; //t is the right_ of the last node
        delete ToBeDel;
    }
}

template <typename Comparable>
typename MyBinarySearchTree<Comparable>::BinaryNode* MyBinarySearchTree<Comparable>::findMin(BinaryNode* t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left_ == nullptr)
        return t;
    return findMin(t->left_);
}

template <typename Comparable>
typename MyBinarySearchTree<Comparable>::BinaryNode* MyBinarySearchTree<Comparable>::findMax(BinaryNode* t) const
{
    if (t != nullptr)
        while (t->right_ != nullptr)
        {
            t = t->right_;
        }
    return t;
}

template <typename Comparable>
bool MyBinarySearchTree<Comparable>::contains(const Comparable& x, BinaryNode* t) const
{
    if (t == nullptr)
        return false;
    if (x < t->element_)
        return contains(x, t->left_);
    if (t->element_ < x)
        return contains(x, t->right_);
    return true;
    //Match
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::makeEmpty(BinaryNode*& t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left_);
        makeEmpty(t->right_);
        delete t;
    }
    t = nullptr;
}

template <typename Comparable>
void MyBinarySearchTree<Comparable>::printTree(BinaryNode* t, std::ostream& out, std::string prefix, bool isLeft) const
{
    if (t != nullptr)
    {
        out << prefix;
        out << (isLeft ? u8"├──" : u8"└──");
        out << t->element_ << std::endl;
        printTree(t->left_, out, prefix + (isLeft ? "│  " : "   "), true);
        printTree(t->right_, out, prefix + (isLeft ? "│  " : "   "), false);
    }
}

template <typename Comparable>
typename MyBinarySearchTree<Comparable>::BinaryNode* MyBinarySearchTree<Comparable>::clone(BinaryNode* t) const
{
    if (t == nullptr)
        return nullptr;
    return new BinaryNode(t->element_, clone(t->left_), clone(t->right_));
}
