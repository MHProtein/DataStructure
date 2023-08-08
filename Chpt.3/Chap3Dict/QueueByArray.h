#pragma once
#include <algorithm>
#include <iostream>

//Recursive Queue
template <class Type, size_t Cap>
class QueueByArray
{
public:
    QueueByArray(): size_(0), capacity_(Cap), front_(-1), rear_(-1)
    {
        data_ = new Type[Cap];
    }

    QueueByArray(const QueueByArray& q): size_(q.size_), capacity_(q.capacity_), front_(q.front_), rear_(q.rear_)
    {
        data_ = new Type[q.capacity_];
        for (size_t i = 0; i != q.capacity_; ++i)
        {
            data_[i] = q.data_[i];
        }
    }

    QueueByArray(QueueByArray&& q) noexcept : size_(std::move(q.size_)), capacity_(std::move(q.capacity_)),
                                              front_(std::move(q.front_)), rear_(std::move(q.rear_))
    {
        q.size_ = 0;
        q.capacity_ = 0;
        q.front_ = 0;
        q.rear_ = 0;
        q.data_ = nullptr;
    }

    QueueByArray& operator=(const QueueByArray& rhs)
    {
        QueueByArray temp(rhs);
        std::swap(*this, temp);
        return *this;
    }

    QueueByArray& operator=(QueueByArray&& rhs) noexcept
    {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(front_, rhs.front_);
        std::swap(rear_, rhs.rear_);
        std::swap(data_, rhs.data_);
        return *this;
    }

    ~QueueByArray()
    {
        size_ = 0;
        capacity_ = 0;
        front_ = 0;
        rear_ = 0;
        data_ = nullptr;
    }

    bool IsFull() const
    {
        return size_ == capacity_;
    }

    bool IsEmpty() const
    {
        return size_ == 0;
    }

    size_t Size() const
    {
        return size_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    Type& GetFront()
    {
        return data_[front_];
    }

    const Type& GetFront() const
    {
        return data_[front_];
    }

    Type& GetBack()
    {
        return data_[rear_];
    }

    const Type& GetBack() const
    {
        return data_[rear_];
    }

    size_t IncrementRear()
    {
        if (++rear_ == capacity_)
        {
            return 0;
        }
        return rear_;
    }

    void Enqueue(const Type& item)
    {
        if (IsFull())
        {
            throw std::exception("enqueue in a full queue");
        }
        if (front_ == -1 && rear_ == -1)
        {
            front_ = rear_ = 0;
        }
        else
        {
            rear_ = IncrementRear();
        }

        ++size_;
        data_[rear_] = item;
    }

    void Enqueue(Type&& item)
    {
        if (IsFull())
        {
            throw std::exception("enqueue in a full queue");
        }
        if (front_ == -1 && rear_ == -1)
        {
            front_ = rear_ = 0;
        }
        else
        {
            rear_ = IncrementRear();
        }

        ++size_;
        data_[rear_] = std::move(item);
    }

    size_t IncrementFront()
    {
        if (++front_ == capacity_)
        {
            return 0;
        }
        return front_;
    }

    void Dequeue()
    {
        if (IsEmpty())
        {
            throw std::exception("dequeue in an empty queue");
        }

        --size_;
        front_ = IncrementFront();
    }

    void Clear()
    {
        while (size_ != 0)
        {
            Dequeue();
        }
    }

    void Print()
    {
        for (int i = 0; i != capacity_; ++i)
        {
            std::cout << data_[i] << std::endl;
        }
    }

private:
    size_t size_;
    size_t capacity_;
    size_t front_;
    size_t rear_;
    Type* data_;
};
