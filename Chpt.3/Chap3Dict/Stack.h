#ifndef STACK_H
#define STACK_H
#include "MyVector/Vector.h"
#include "MyList/List.h"

template <typename Type, typename Container = Vector<Type>>
class Stack
{
public:
    Stack()
    {
        data_ = new Container;
    }

    Stack(const Stack& stk)
    {
        data_ = new Container(stk.data_);
    }

    Stack(Stack&& stk) noexcept : data_(std::move(stk.data_))
    {
        stk.data_ = nullptr;
    }

    Stack& operator=(const Stack& rhs)
    {
        Stack temp = rhs;
        std::swap(*this, temp);
        return *this;
    }

    Stack& operator=(Stack&& rhs) noexcept
    {
        std::swap(data_, rhs.data_);
        return *this;
    }

    size_t size() const
    {
        return data_->size();
    }

    bool empty() const
    {
        return data_->empty();
    }

    Type& top()
    {
        return data_->back();
    }

    const Type& top() const
    {
        return data_->back();
    }

    void push(const Type& item)
    {
        data_->push_back(item);
    }

    void push(Type&& item)
    {
        data_->push_back(std::forward<Type&&>(item));
    }

    void pop()
    {
        data_->pop_back();
    }

private:
    Container* data_;
};
#endif
