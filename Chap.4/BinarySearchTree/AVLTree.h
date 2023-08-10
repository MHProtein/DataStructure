#pragma once

template<class Type>
class AVLTree
{

    static const int MAX_ALLOWED_HEIGHT_IMBALANCE = 1;
    
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
        AVLTree temp = rhs;
        std::swap(temp, *this);
        return *this;
    }

    AVLTree& operator=(AVLTree&& rhs) noexcept
    {
        std::swap(root_, rhs.root_);
        return *this;
    }

    ~AVLTree()
    {
        MakeEmpty(root_);
    }

    bool IsEmpty() const
    {
        return root_ == nullptr;
    }

    void MakeEmpty()
    {
        MakeEmpty(root_);
    }

    Type& FindMax() const 
    {
        return FindMax(root_)->element;
    }

    Type& FindMin() const
    {
        return FindMin(root_)->element;
    }

    bool Contain(const Type& item) const
    {
        return Contain(item, root_);
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
        PrintTree(out, root_, " ", false);
    }

private:
    struct AVLNode
    {
        AVLNode(const Type& Elem, AVLNode* Left, AVLNode* Right, int Height = 0) : element(Elem), left(Left), right(Right), height(Height){ }
        AVLNode(Type&& Elem, AVLNode* Left, AVLNode* Right, int Height = 0) noexcept : element(std::move(Elem)), left(Left), right(Right), height(Height){ }

        Type element;
        AVLNode* left;
        AVLNode* right;
        int height;
    };

    AVLNode* root_;

    int Height(AVLNode* t)
    {
        if(t == nullptr)
            return -1;
        return t->height;
    }
    
    AVLNode* Clone(AVLNode* t)
    {
        if(t == nullptr)
            return nullptr;
        AVLNode* node = new AVLNode(t->element, Clone(t->left), Clone(t->right), t->height);
        return node;
    }

    void MakeEmpty(AVLNode*& t)
    {
        if(t == nullptr)
            return;
        MakeEmpty(t->left);
        MakeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    AVLNode* FindMax(AVLNode* t) const
    {
        if(t == nullptr)
            return nullptr;
        if(t->right == nullptr)
            return t;
        return FindMax(t->right);
    }

    AVLNode* FindMin(AVLNode* t) const
    {
        if(t == nullptr)
            return nullptr;
        if(t->left == nullptr)
            return t;
        return FindMin(t->left);
    }

    bool Contain(const Type& item, AVLNode* t) const
    {
        if(t == nullptr)
            return false;
        if(item < t->element)
            return Contain(item, t->left);
        if(t->element < item)
            return Contain(item, t->right);
        return true;
    }

    void Balance(AVLNode*& t)
    {
        if(t == nullptr)
            return;
        if(Height(t->left) - Height(t->right) > MAX_ALLOWED_HEIGHT_IMBALANCE)
        {
            if(Height(t->left->left) >= Height(t->left->right))
                RotateWithLeftChild(t);
            else
                DoubleRotateWithLeftChild(t);
        }
        if(Height(t->right) - Height(t->left) > MAX_ALLOWED_HEIGHT_IMBALANCE)
        {
            if(Height(t->right->right) >= Height(t->right->left))
                RotateWithRightChild(t);
            else
                DoubleRotateWithRightChild(t);
        }
        t->height = std::max(Height(t->left), Height(t->right)) + 1;
    }

    void RotateWithLeftChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(Height(k2->left), Height(k2->right)) + 1;
        k1->height = std::max(Height(k1->left), Height(k2)) + 1;
        k2 = k1;
    }

    void RotateWithRightChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = std::max(Height(k2->right), Height(k2->left)) + 1;
        k1->height = std::max(Height(k1->right), Height(k2)) + 1;
        k2 = k1;
    }

    void DoubleRotateWithLeftChild(AVLNode*& k3)
    {
        RotateWithRightChild(k3->left);
        RotateWithLeftChild(k3);
    }

    void DoubleRotateWithRightChild(AVLNode*& k3)
    {
        RotateWithLeftChild(k3->right);
        RotateWithRightChild(k3);
    }

    void Insert(const Type& item, AVLNode*& t)
    {
        if(t == nullptr)
            t = new AVLNode(item, nullptr, nullptr);
        else if(item < t->element)
            Insert(item, t->left);
        else if(t->element < item)
            Insert(item, t->right);
        Balance(t);
    }

    void Insert(Type&& item, AVLNode*& t)
    {
        if(t == nullptr)
            t = new AVLNode(std::move(item), nullptr, nullptr);
        else if(item < t->element)
            Insert(std::forward<Type&&>(item), t->left);
        else if(t->element < item)
            Insert(std::forward<Type&&>(item), t->right);
        Balance(t);
    }

    void Remove(const Type& item, AVLNode*& t)
    {
        if(t == nullptr)
            return;
        if(item < t->element)
            Remove(item, t->left);
        else if(t->element < item)
            Remove(item, t->right);
        else if(t->left != nullptr && t->right != nullptr)
        {
            t->element = FindMax(t->right)->element;
            Remove(t->element, t->right);
        }
        else
        {
            AVLNode* OldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete t;
        }
        Balance(t);
    }

    void PrintTree(std::ostream& out, AVLNode* t, std::string prefix, bool IsLeft)
    {
        if (t == nullptr)
            return;
        
        out << prefix;
        out << (IsLeft ? u8"├──" : u8"└──");
        out << t->element << std::endl;
        PrintTree(out, t->left, prefix + (IsLeft ? u8"│  " : u8"   "), true);
        PrintTree(out, t->right, prefix + (IsLeft ? u8"│  " : u8"   "), false);
    }
};