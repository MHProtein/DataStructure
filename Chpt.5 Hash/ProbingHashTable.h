#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

template<class HashedObj>
class ProbingHashTable
{
public:
    explicit ProbingHashTable(int size = 101);

    bool contains(const HashedObj& x) const;

    void makeEmpty();
    bool insert(const HashedObj& x);
    bool insert(HashedObj&& x);
    bool remove(const HashedObj& x);

    void print()
    {
        for(const auto& i : array_)
        {
            if(i.info == EntryType::ACTIVE)
                std::cout << i.element << std::endl;
        }
    }
    
    enum EntryType { ACTIVE, EMPTY, DELETED };
    
private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
            : element(e), info(i) { }
        
        HashEntry(HashedObj&& e, EntryType i = EMPTY)
            : element(std::move(e)), info(i) { }
    };

    std::vector<HashEntry> array_;
    int current_size_;

    bool isActive(int currentPos) const;
    int findPos(const HashedObj& x) const;
    void rehash();
    size_t myhash(const HashedObj& x) const;
    size_t doubleHash(const HashedObj& x) const;
    int nextPrime(int size);
};

template <class HashedOjb>
ProbingHashTable<HashedOjb>::ProbingHashTable(int size) : array_(nextPrime(size))
{
    makeEmpty();
}

template <class HashedOjb>
bool ProbingHashTable<HashedOjb>::contains(const HashedOjb& x) const
{
    return isActive(findPos(x));
}

template <class HashedOjb>
void ProbingHashTable<HashedOjb>::makeEmpty()
{
    current_size_ = 0;
    for(auto& entry : array_)
        entry.info = EntryType::EMPTY;
}

template <class HashedOjb>
bool ProbingHashTable<HashedOjb>::insert(const HashedOjb& x)
{
    int currentPos = findPos(x);
    if(isActive(currentPos))
        return false;
    
    array_[currentPos].element = x;
    array_[currentPos].info = EntryType::ACTIVE;

    if(++current_size_ > array_.size() / 2)
        rehash();
    return true;
}

template <class HashedOjb>
bool ProbingHashTable<HashedOjb>::insert(HashedOjb&& x)
{
    int currentPosition = findPos(std::forward<HashedOjb&&>(x));
    if(isActive(currentPosition))
        return false;
    
    array_[currentPosition] = std::move(x);
    array_[currentPosition].info = EntryType::ACTIVE;

    if(current_size_ > array_.size())
        rehash();
    return true;
}

template <class HashedOjb>
bool ProbingHashTable<HashedOjb>::remove(const HashedOjb& x)
{
    int currentPos = findPos(x);
    if(!isActive(currentPos))
        return false;

    array_[currentPos].info = EntryType::DELETED;
    return true;
}

template <class HashedOjb>
bool ProbingHashTable<HashedOjb>::isActive(int currentPos) const
{
    return array_[currentPos].info == EntryType::ACTIVE;
}

template <class HashedOjb>
int ProbingHashTable<HashedOjb>::findPos(const HashedOjb& x) const
{
    int offset = 1;
    int currentPos = myhash(x);
    
    while(array_[currentPos].info != EntryType::EMPTY && array_[currentPos].element != x)
    {
        currentPos += offset;
        offset += 2;
        if(currentPos >= array_.size())
            currentPos-= array_.size();
    }
    return currentPos;
}

template <class HashedOjb>
void ProbingHashTable<HashedOjb>::rehash()
{
    std::vector<HashEntry> oldArray = array_;

    array_.resize(nextPrime(2 * oldArray.size()));
    for(auto& entry: array_)
        entry.info = EntryType::EMPTY;

    current_size_ = 0;
    for(auto& entry: oldArray)
        if(entry.info == EntryType::ACTIVE)
            insert(std::move(entry.element));
}

template <class HashedOjb>
size_t ProbingHashTable<HashedOjb>::myhash(const HashedOjb& x) const
{
    static std::hash<HashedOjb> hs;
    return hs(x) % array_.size();
}

template <class HashedOjb>
size_t ProbingHashTable<HashedOjb>::doubleHash(const HashedOjb& x) const
{
    //no necessity to use it in quadratic probings
    static std::hash<HashedOjb> hs;
    int R = array_.size() % 2 ? array_.size() : array_.size() + 1; //a prime number smaller than array.size()
    size_t newHash = R - hs(x) % R - 1; //hash2(x) = R - (x mod R)
    int i = 1;
    while(array_[newHash * i].info == EntryType::ACTIVE)
    {
        ++i;
    }
    return i * newHash;
}

template <class HashedOjb>
int ProbingHashTable<HashedOjb>::nextPrime(int size)
{
    int newSize = size;
    while(true)
    {
        bool isPrime = true;
        for(int i = 2; i <= std::sqrt(size); ++i)
        {
            if(size % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            break;
        ++newSize;
    }
    
    return newSize;
}
