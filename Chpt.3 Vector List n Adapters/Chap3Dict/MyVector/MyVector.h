#ifndef MYVECTOR_H
#define MYVECTOR_H

#pragma once
#include <memory>
#include <stack>
#include <vector>

template <class Type>
class MyVector
{
public:
    using iterator = Type*;
    using const_iterator = const Type*;

    explicit MyVector(int initSize = 0): theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
    {
        Objects = new Type[theCapacity];
    }

    MyVector(const MyVector& rhs): theSize(rhs.theSize), theCapacity(rhs.theCapacity)
    {
        Objects = new Type[theCapacity];
        for (int i = 0; i < rhs.theSize; ++i)
        {
            Objects[i] = std::move(rhs.Objects[i]);
        }
    }

    MyVector& operator=(const MyVector& rhs)
    {
        MyVector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~MyVector()
    {
        delete[] Objects;
    }

    MyVector(MyVector&& rhs) noexcept : theSize(rhs.theSize), theCapacity(rhs.theCapacity), Objects(rhs.Objects)
    {
        rhs.Objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    MyVector& operator=(MyVector&& rhs) noexcept
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(Objects, rhs.Objects);
        return *this;
    }

    void resize(const int newSize)
    {
        if (newSize > theCapacity)
        {
            reserve(newSize * 2);
            theSize = newSize;
        }
    }

    void reserve(const int newCapacity)
    {
        if (newCapacity < theSize)
        {
            return;
        }

        Type* newArray = new Type[newCapacity];
        for (int i = 0; i < theSize; ++i)
        {
            newArray[i] = std::move(Objects[i]);
        }
        std::swap(Objects, newArray);
        delete[] newArray;
    }

    const Type& operator[](int index) const
    {
        return Objects[index];
    }

    Type& operator[](int index)
    {
        return const_cast<Type&>(operator[](index));
    }

    bool empty() const
    {
        return size() == 0;
    }

    size_t size() const
    {
        return theSize;
    }

    size_t capacity() const
    {
        return theCapacity;
    }

    void push_back(const Type& Object)
    {
        if (theSize == theCapacity)
        {
            reserve(2 * capacity() + 1);
        }
        Objects[theSize++] = std::move(Object);
    }

    void pop_back()
    {
        --theSize;
    }

    const Type& back() const
    {
        return Objects[size() - 1];
    }

    Type* begin()
    {
        return &Objects[0];
    }

    const Type* begin() const
    {
        return &Objects[0];
    }

    const Type* cbegin() const
    {
        return begin();
    }

    Type* end()
    {
        return &Objects[theSize];
    }

    const Type* end() const
    {
        return &Objects[theSize];
    }

    const Type* cend() const
    {
        return end();
    }

    static const int SPARE_CAPACITY = 16;

private:
    int theSize;
    int theCapacity;
    Type* Objects;
};
#endif
