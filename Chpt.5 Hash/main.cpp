#include <random>
#include <unordered_map>

#include "ProbingHashTable.h"

int main()
{
    static std::default_random_engine e(time(nullptr));
    ProbingHashTable<int> ht;
    for(int i = 0; i != 10; ++i)
    {
        ht.insert(i);
    }
    static std::hash<int> h;
    std::cout <<"print"<<std::endl;
    ht.print();
    
}