#ifndef MYLIST_H
#define MYLIST_H

#include <algorithm>
#include <stdexcept>

template <class Type>
class MyList
{
    //node
    struct Node
    {
        Node(const Type& Data = Type(), Node* Prev = nullptr, Node* Next = nullptr)
            : data(Data), prev(Prev), next(Next)
        {
        }

        Node(Type&& Data, Node* Prev = nullptr, Node* Next = nullptr)
            : data(std::move(Data)), prev(Prev), next(Next)
        {
        }

        Type data;
        Node* prev;
        Node* next;
    };

public:
    //const_iterator
    class const_iterator
    {
    public:
        const_iterator(): current_(nullptr), this_list_(nullptr)
        {
        }

        const Type& operator*() const
        {
            return retrieve();
        }

        const_iterator& operator++()
        {
            assertIsValid();
            current_ = current_->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            assertIsValid();
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator& rhs) const
        {
            return current_ == rhs.current_ && this_list_ == rhs.this_list_;
        }

        bool operator!=(const const_iterator& rhs) const
        {
            return !operator==(rhs);
        }

    protected:
        Node* current_;
        const MyList<Type>* this_list_;

        Type& retrieve() const
        {
            return current_->data;
        }

        const_iterator(Node* ptr, const MyList<Type>* this_list): current_(ptr), this_list_(this_list)
        {
        }

        void assertIsValid() const
        {
            if (this_list_ == nullptr || current_ == nullptr || current_ == this_list_->head_ || current_ == this_list_
                ->tail_)
            {
                throw std::exception("IteratorOutOfBoundException");
            }
        }

        friend class MyList;
    };

    //iterator
    class iterator : public const_iterator
    {
    public:
        iterator()
        {
        }

        Type& operator*()
        {
            return const_iterator::retrieve();
        }

        const Type& operator*() const
        {
            return const_iterator::operator*();
        }

        iterator& operator++()
        {
            const_iterator::assertIsValid();
            this->current_ = this->current_->next;
            return *this;
        }

        iterator operator++(int)
        {
            const_iterator::assertIsValid();
            iterator temp = *this;
            ++(*this);
            return temp;
        }

    protected:
        iterator(Node* ptr, const MyList<Type>* this_list): const_iterator(ptr, this_list)
        {
        }

        friend class MyList;
    };

public:
    //Big Five
    MyList()
    {
        init();
    }

    ~MyList()
    {
        clear();
        delete head_;
        delete tail_;
    }

    MyList(const MyList& rhs)
    {
        init();
        for (const auto& item : rhs)
        {
            push_back(item);
        }
    }

    MyList(MyList&& rhs) noexcept : size_(rhs.size_), head_(rhs.head_), tail_(rhs.tail_)
    {
        rhs.size_ = 0;
        rhs.head_ = nullptr;
        rhs.tail_ = nullptr;
    }

    MyList& operator=(const MyList& rhs)
    {
        MyList temp = rhs;
        std::swap(temp, *this);
        return *this;
    }

    MyList& operator=(MyList&& rhs) noexcept
    {
        std::swap(size_, rhs.size_);
        std::swap(head_, rhs.head_);
        std::swap(tail_, rhs.tail_);
        return *this;
    }

    iterator begin()
    {
        return iterator(head_->next, this);
    }

    const_iterator begin() const
    {
        return const_iterator(head_->next, this);
    }

    const_iterator cbegin() const
    {
        return begin();
    }

    iterator end()
    {
        return iterator(tail_, this);
    }

    const_iterator end() const
    {
        return iterator(tail_, this);
    }

    const_iterator cend() const
    {
        return end();
    }

    size_t size() const { return size_; }
    bool empty() const { return size() == 0; }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    Type& front()
    {
        return *head_->next;
    }

    const Type& front() const
    {
        return const_cast<const Type&>(front());
    }

    Type& back()
    {
        return *tail_->prev;
    }

    const Type& back() const
    {
        return const_cast<const Type&>(back());
    }

    void push_front(const Type& item)
    {
        insert(begin(), item);
    }

    void push_front(Type&& item)
    {
        insert(begin(), std::forward<Type&&>(item));
    }

    void pop_front()
    {
        erase(begin());
    }

    void push_back(const Type& item)
    {
        insert(end(), item);
    }

    void push_back(Type&& item)
    {
        insert(end(), std::forward<Type&&>(item));
    }

    void pop_back()
    {
        erase(--end());
    }

    iterator insert(iterator it, const Type& item)
    {
        Node* node = it.current_;
        ++size_;
        Node* new_node = new Node(item, node->prev, node);
        node->prev->next = new_node;
        node->prev = new_node;
        return iterator(new_node, this);
    }

    iterator insert(iterator it, Type&& item)
    {
        it.assertIsValid();
        CheckListMatching();

        Node* ptr = it.current_;
        ++size_;
        Node* new_node = new Node(std::move(item), ptr->prev, ptr);
        ptr->prev->next = new_node;
        ptr->prev = new_node;
        return iterator(new_node, this);
    }

    iterator erase(iterator it)
    {
        it.assertIsValid();
        CheckListMatching(it);

        if (it.this_list_ != this)
            throw std::exception("IteratorMismatchException");

        Node* node = it.current_;
        iterator returnVal(node->next, this);
        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete node;
        --size_;
        return returnVal;
    }

    iterator erase(iterator from, iterator to)
    {
        for (iterator it = from; it != to;)
        {
            it.assertIsValid();
            CheckListMatching(it);
            erase(it);
        }
        return iterator(to, this);
    }

private:
    void init()
    {
        size_ = 0;
        head_ = new Node;
        tail_ = new Node;
        tail_->prev = head_;
        head_->next = tail_;
    }

    void CheckListMatching(iterator& it)
    {
        if (it.this_list_ != this)
            throw std::exception("IteratorMismatchException");
    }

    size_t size_;
    Node* head_;
    Node* tail_;
};
#endif
