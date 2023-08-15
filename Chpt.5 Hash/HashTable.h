#pragma once
#include <list>
#include <vector>
#include <cmath>

template<class HashedObj>
class HashTable
{
public:
    explicit HashTable(int size = 101);

    bool contains(const HashedObj& x) const;

    void makeEmpty();
    bool insert(const HashedObj& x);
    bool insert(HashedObj&& x);
    bool remove(const HashedObj& x);
    
private:
    std::vector<std::list<HashedObj>> theLists;
    size_t currentSize;

    void rehash();
    size_t myhash(const HashedObj& x) const;
    int nextPrime(int size);
};

template <class HashedObj>
HashTable<HashedObj>::HashTable(int size) : theLists(nextPrime(size))
{
    currentSize = 0;
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for (const auto& list : theLists)
    {
        list.clear();
    }
}

template <class HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj& x)
{
    auto& whichList = theLists[myhash(x)];
    if(std::find(whichList.cbegin(), whichList.cend(), x) != whichList.end())
        return false;

    whichList.push_back(x);

    if(++currentSize > theLists.size())
        rehash();
    
    return true;
}

template <class HashedObj>
bool HashTable<HashedObj>::insert(HashedObj&& x)
{
    auto& whichList = theLists[myhash(std::move(x))];
    if(std::find(whichList.cbegin(), whichList.cend(), std::move(x)) != whichList.end())
        return false;
    whichList.push_back(std::move(x));

    if(++currentSize > theLists.size())
        rehash();
    return true;
}

template <class HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj& x) const
{
    auto& whichList = theLists[myhash(x)];
    return std::find(whichList.cbegin(), whichList.cend(), x) != whichList.cend();
}

template <class HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj& x)
{
    auto& whichList = theLists[myhash(x)];
    auto it = std::find(whichList.begin(), whichList.end(), x);
    if(it == whichList.end())
        return false;

    whichList.erase(it);
    --currentSize;
    return true;
}

template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
    std::vector<std::list<HashedObj>> oldLists = theLists;

    theLists.resize(nextPrime(currentSize * 2));
    for(auto & thisList : theLists)
        thisList.clear();

    currentSize = 0;
    for(auto& thisList : oldLists)
        for(auto& x : thisList)
            insert(std::move(x));
}

template <class HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj& x) const
{
    static std::hash<HashedObj> hf;
    return hf(x) % theLists.size();
}

template <class HashedObj>
int HashTable<HashedObj>::nextPrime(int size)
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
