#pragma once
#include <string>

template<class HashType>
class hash;

template<>
class hash<std::string>
{
public:
    size_t operator()(const std::string& str)
    {
        size_t hashVal = 0;
        for(const auto& ch : str)
        {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal;
    }
};

size_t hash(const std::string& key, size_t tableSize);

