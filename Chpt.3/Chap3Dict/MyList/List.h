#ifndef LIST_H
#define LIST_H

#include <algorithm>

template <class Type>
class List
{
    struct Node
    {
        Node(const Type& Data = Type(), Node* Prev = nullptr, Node* Next = nullptr): data(Data), prev(Prev), next(Next)
        {
        }

        Node(Type&& Data, Node* Prev = nullptr, Node* Next = nullptr): data(std::move(Data)), prev(Prev), next(Next)
        {
        }

        Type data;
        Node* prev;
        Node* next;
    };

public:
    friend void swap(List& lhs, List& rhs);

    class const_iterator
    {
    public:
        const_iterator(): current_(nullptr), this_list_(nullptr)
        {
        }

        const Type& operator*() const
        {
            assertException();
            return current_->data;
        }

        const_iterator& operator++()
        {
            assertException();
            current_ = current_->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            assertException();
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }

        const_iterator& operator--()
        {
            assertException();
            this->current_ = this->current_->prev;
            return *this;
        }

        const_iterator operator--(int)
        {
            assertException();
            const_iterator temp = *this;
            --(*this);
            return temp;
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
        const List* this_list_;

        const_iterator(Node* Current, const List* ThisList): current_(Current), this_list_(ThisList)
        {
        }

        Type& dereference() const
        {
            return current_->data;
        }

        friend class List;

        void assertException() const
        {
            if (current_ == nullptr || this_list_ == nullptr || current_ == this_list_->tail_ || current_ == this_list_
                ->head_)
            {
                throw std::exception("Iterator Out Of Range");
            }
        }
    };

    class iterator : public const_iterator
    {
    public:
        iterator(): const_iterator()
        {
        }

        Type& operator*()
        {
            const_iterator::assertException();
            return const_iterator::dereference();
        }

        const Type& operator*() const
        {
            const_iterator::assertException();
            return const_iterator::operator*();
        }

        iterator& operator++()
        {
            const_iterator::assertException();
            this->current_ = this->current_->next;
            return *this;
        }

        iterator operator++(int)
        {
            const_iterator::assertException();
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--()
        {
            //const_iterator::assertException();
            this->current_ = this->current_->prev;
            return *this;
        }

        iterator operator--(int)
        {
            //::assertException();
            iterator temp = *this;
            --(*this);
            return temp;
        }

    protected:
        iterator(Node* Current, const List* ThisList): const_iterator(Current, ThisList)
        {
        }

        friend class List;
    };

public:
    List()
    {
        init();
    }

    List(const std::initializer_list<Type>& init_list)
    {
        init();
        for (const auto& item : init_list)
        {
            push_back(item);
        }
    }

    List(const List& lst)
    {
        init();
        for (const auto& item : lst)
        {
            push_back(item);
        }
    }

    List(List&& lst) noexcept : size_(std::move(lst.size_)), head_(std::move(lst.head_)), tail_(std::move(lst.tail_))
    {
        lst.size_ = 0;
        lst.head_ = nullptr;
        lst.tail_ = nullptr;
    }

    List& operator=(const List& rhs)
    {
        List temp = rhs;
        std::swap(*this, temp);
        return *this;
    }

    List& operator=(List&& rhs) noexcept
    {
        std::swap(size_, rhs.size_);
        std::swap(head_, rhs.head_);
        std::swap(tail_, rhs.tail_);
        return *this;
    }

    ~List()
    {
        size_ = 0;
        delete head_;
        delete tail_;
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

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
        return const_iterator(tail_, this);
    }

    const_iterator cend() const
    {
        return end();
    }

    Type& front()
    {
        return head_->next->data;
    }

    const Type& front() const
    {
        return head_->next->data;
    }

    Type& back()
    {
        return tail_->prev->data;
    }

    const Type& back() const
    {
        return tail_->prev->data;
    }

    iterator insert(iterator it, const Type& item)
    {
        if (it != end())
        {
            it.assertException();
        }
        IsInListExceptionCheck(it);

        Node* new_node = new Node(item, it.current_->prev, it.current_);
        it.current_->prev->next = new_node;
        it.current_->prev = new_node;
        size_++;
        return iterator(new_node, this);
    }

    iterator insert(iterator it, Type&& item)
    {
        if (it != end())
        {
            it.assertException();
        }
        IsInListExceptionCheck(it);

        Node* new_node = new Node(std::move(item), it.current_->prev, it.current_);
        it.current_->prev->next = new_node;
        it.current_->prev = new_node;
        size_++;
        return iterator(new_node, this);
    }

    iterator erase(iterator it)
    {
        it.assertException();
        IsInListExceptionCheck(it);
        iterator return_val(it.current_->next, this);
        it.current_->next->prev = it.current_->prev;
        it.current_->prev->next = it.current_->next;
        delete it.current_;
        size_--;
        return return_val;
    }

    iterator erase(iterator from, iterator to)
    {
        for (iterator it = from; it != to;)
        {
            it = erase(it);
        }

        return to;
    }

    void push_back(const Type& item)
    {
        insert(end(), item);
    }

    void push_back(Type&& item)
    {
        insert(end(), std::forward<Type&&>(item));
    }

    void push_front(const Type& item)
    {
        insert(begin(), item);
    }

    void push_front(Type&& item)
    {
        insert(begin(), std::forward<Type&&>(item));
    }

    void pop_back()
    {
        erase(--end());
    }

    void pop_front()
    {
        erase(begin());
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    void SwapNodes(iterator former, iterator latter)
    {
        Node* node1 = former.current_;
        Node* node2 = latter.current_;

        node1->prev->next = node2;
        node2->next->prev = node1;

        node1->next = node2->next;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next = node1;
    }

private:
    void IsInListExceptionCheck(iterator it)
    {
        if (it.this_list_ != this)
        {
            throw std::exception("Iterator MisMatches the List");
        }
    }

    void init()
    {
        size_ = 0;
        head_ = new Node;
        tail_ = new Node;
        head_->next = tail_;
        tail_->prev = head_;
    }

    size_t size_;
    Node* head_;
    Node* tail_;
};

#endif
