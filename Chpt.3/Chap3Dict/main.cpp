#include <codecvt>
#include <forward_list>
#include <iostream>
#include "MyVector/Vector.h"
#include <vector>
#include <sstream>
#include <list>
#include <math.h>
#include <queue>

#include "MyList/List.h"
#include "Stack.h"
#include "StackApplication.h"
#include "QueueByArray.h"

void PrintLots(const List<int>& L, const List<int>& P)
{
    List<int> subscripts;
    for (const auto& item : L)
    {
        subscripts.push_back(item);
    }
    int cnt = 0;
    for (const auto& item : P)
    {
        bool is_next_sub = false;
        if (cnt == subscripts.front())
        {
            std::cout << item << std::endl;
            is_next_sub = true;
        }
        if (is_next_sub)
            subscripts.pop_front();
        ++cnt;
    }
}

class Josephus
{
public:
    Josephus(const size_t& N, const size_t& M): n_(N), m_(M), current_(0)
    {
        people_ = new Person[n_]();
        for (size_t i = 0; i != n_; ++ i)
        {
            people_[i].num_ = i + 1;
        }
    }

    ~Josephus()
    {
        n_ = 0;
        m_ = 0;
        current_ = 0;
        delete people_;
    }

    size_t Winner()
    {
        if (m_ == 0)
        {
            return people_[n_ - 1].num_;
        }

        current_ = 0;
        size_t NotOut = n_;
        size_t passes = 0;
        while (NotOut != 1)
        {
            Pass();
            ++passes;
            if (passes == m_)
            {
                people_[current_].Out();
                Pass(); //Give the potato to the survived guy
                --NotOut;
                passes = 0;
            }
        }
        size_t Winner = people_[current_].num_;
        return Winner;
    }

private:
    void Pass()
    {
        if (++current_ == n_)
        {
            current_ = 0;
        }
        while (people_[current_].is_out_)
        {
            if (++current_ == n_)
            {
                current_ = 0;
            }
        }
    }

    struct Person
    {
        Person(): num_(0), is_out_(false)
        {
        }

        explicit Person(const size_t& Num): num_(Num), is_out_(false)
        {
        }

        explicit Person(size_t&& Num) noexcept : num_(std::move(Num)), is_out_(false)
        {
        }

        void Out()
        {
            is_out_ = true;
        }

        size_t num_;
        bool is_out_;
    };

    size_t n_;
    size_t m_;
    size_t current_;
    Person* people_;
};

int main()
{
    Josephus jos(1000001, 2);
    std::cout << "winner: " << jos.Winner() << std::endl;
    std::cout << clock() << std::endl;
}
