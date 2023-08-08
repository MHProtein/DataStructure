#pragma once
#include "MyList/List.h"

template <class Type>
class QueueByList
{
public:
    QueueByList()
    {
        data_ = new List<Type>;
    }

    QueueByList(const QueueByList& q)
    {
        data_ = new List<Type>(q.data_);
    }

    QueueByList(QueueByList&& q) noexcept : data_(std::move(q.data_))
    {
    }

    QueueByList& operator=(const QueueByList& rhs)
    {
        QueueByList temp(rhs);
        std::swap(*this, temp);
        return *this;
    }

    QueueByList& operator=(QueueByList&& rhs) noexcept
    {
        std::swap(data_, rhs.data_);
        return *this;
    }

    ~QueueByList()
    {
        delete data_;
    }

    size_t size() const
    {
        return data_->size();
    }

    bool empty() const
    {
        return data_->empty();
    }

    Type& front()
    {
        return data_->front();
    }

    const Type& front() const
    {
        return data_->front();
    }

    Type& back()
    {
        return data_->back();
    }

    const Type& back() const
    {
        return data_->back();
    }

    void push(const Type& item) const
    {
        data_->push_back(item);
    }

    void push(Type&& item) const
    {
        data_->push_back(std::forward<Type&&>(item));
    }

    void pop()
    {
        data_->pop_front();
    }

    void clear()
    {
        data_->clear();
    }

private:
    List<Type>* data_;
};
