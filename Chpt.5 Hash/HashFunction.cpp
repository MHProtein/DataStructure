#include "HashFunction.h"
#include <string>
size_t hash(const std::string& key, size_t tableSize)
{
    size_t hashVal = 0;
    for(const auto& ch : key)
    {
        hashVal = 37 * hashVal + ch;
    }

    return hashVal % tableSize;
}

