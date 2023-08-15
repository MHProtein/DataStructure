#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>
#include <stack>
#include <string>

template <class Type>
class Vector
{
    size_t InitialCapacity = 16;

public:
    using iterator = Type*;
    using const_iterator = const Type*;

    Vector(const size_t InitialSize = 0): size_(0), capacity_(InitialCapacity + InitialSize)
    {
        Objects = new Type[capacity_];
        LastElem = Objects - 1;
    }

    Vector(const Vector& rhs): size_(rhs.size_), capacity_(rhs.capacity_)
    {
        Objects = new Type[capacity_];
        for (size_t i = 0; i != rhs.size_; ++i)
        {
            Objects[i] = std::move(rhs.Objects[i]);
        }
        LastElem = Objects + size_ - 1;
    }

    Vector(Vector&& rhs) noexcept: size_(std::move(rhs.size_)), capacity_(std::move(rhs.capacity_)),
                                   Objects(std::move(rhs.Objects)),
                                   LastElem(std::move(rhs.LastElem))
    {
        rhs.capacity_ = 0;
        rhs.size_ = 0;
        rhs.Objects = nullptr;
    }

    Vector& operator=(const Vector& rhs)
    {
        Vector temp = std::move(rhs);
        std::swap(*this, temp);
        return *this;
    }

    Vector& operator=(Vector&& rhs) noexcept
    {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(Objects, rhs.Objects);
        std::swap(LastElem, rhs.LastElem);
        return *this;
    }

    ~Vector()
    {
        delete[] Objects;
    }

    void push_back(const Type& item)
    {
        if (size_ == capacity_)
        {
            reallocate(capacity_ * 2 + 1);
        }
        *(++LastElem) = item;
        ++size_;
    }

    void pop_back()
    {
        *(LastElem--) = 0;
        --size_;
    }

    bool empty() const
    {
        return size() == 0;
    }

    void resize(size_t NewSize)
    {
        if (NewSize > size() && size() <= capacity())
        {
            size_t difference = NewSize - size();
            for (int i = 0; i != difference; ++i)
                push_back(Type());
        }
        else if (NewSize > size() && size() > capacity())
        {
            reallocate(NewSize);
            size_t difference = NewSize - size();
            for (int i = 0; i != difference; ++i)
                push_back(Type());
        }
        else if (NewSize < size())
        {
            size_t difference = size() - NewSize;
            for (int i = 0; i != difference; ++i)
                pop_back();
        }
    }

    void reserve(size_t NewCapacity)
    {
        if (NewCapacity >= capacity())
            reallocate(NewCapacity);
    }

    void insert(Type* it, const Type& item)
    {
        std::cout << "insert " + std::to_string(item) << std::endl;
        if (size() == capacity())
        {
            //After the allocation, iterators go invalid.
            size_t difference = it - begin();
            reallocate(capacity() * 2);
            it = begin() + difference;
        }
        for (Type* ite = LastElem; ite >= it; --ite)
        {
            *(ite + 1) = *ite;
        }
        *it = std::move(item);
        ++LastElem;
        ++size_;
    }

    void erase(Type* it)
    {
        for (Type* ite = it + 1; ite != LastElem + 1; ++ite)
        {
            *(ite - 1) = *ite;
        }
        --size_;
        *LastElem-- = Type();
    }

    void erase(Type* from, Type* to)
    {
        //remove elements from "from" to the element before "to"
        size_t cut_length = to - from;
        size_t back_length = LastElem - (to - 1);

        Type* remove_to_target;
        if (cut_length > back_length)
        {
            remove_to_target = LastElem - back_length;
        }
        else
        {
            remove_to_target = LastElem;
        }
        //move the back part to the cut part
        for (size_t i = 0; i != back_length; ++i)
        {
            *(from + i) = *(to + i);
        }
        //reset the left part behind the last element to zero
        for (Type* it = from + back_length; it != remove_to_target; ++it)
        {
            *it = 0;
        }
        size_ -= cut_length;
        LastElem = from + back_length - 1;
    }

    size_t size() const
    {
        return size_;
    }

    size_t capacity() const
    {
        return capacity_;
    }

    const Type* begin() const
    {
        return &Objects[0];
    }

    Type* begin()
    {
        return &Objects[0];
    }

    const Type* cbegin() const
    {
        return begin();
    }

    Type* end()
    {
        return LastElem + 1;
    }

    const Type* end() const
    {
        return LastElem + 1;
    }

    const Type* cend() const
    {
        return end();
    }

    Type& back()
    {
        return *(end() - 1);
    }

    const Type& back() const
    {
        return *(end() - 1);
    }

private:
    void reallocate(size_t NewCapacity)
    {
        if (NewCapacity <= capacity_)
        {
            return;
        }

        Type* temp = new Type[NewCapacity];

        for (size_t i = 0; i != size_; ++i)
        {
            temp[i] = std::move(Objects[i]);
        }

        std::swap(temp, Objects);
        delete[] temp;
        LastElem = Objects + size_ - 1;
        capacity_ = NewCapacity;
    }

    size_t size_;
    size_t capacity_;
    Type* Objects;
    Type* LastElem;
};
#endif
