#pragma once
#include <string>

class Employee
{
public:

    Employee() : name(std::string()), salary(0.0), seniority(0) { }
    Employee(const std::string& Name, double Salary, int Seniority) : name(Name), salary(Salary), seniority(Seniority){ }
    Employee(std::string&& Name, double Salary, int Seniority) : name(std::move(Name)), salary(Salary), seniority(Seniority){ }
    
    const std::string getName() const { return name; }

    bool operator==(const Employee& rhs) const
    {
        return getName() == rhs.getName();
    }
    bool operator!=(const Employee& rhs) const
    {
        return !operator==(rhs);
    }
    
private:
    std::string name;
    double salary;
    int seniority; //zili paihang
};

template<class HashType>
class hash;

template<>
class hash<Employee>
{
public:
    size_t operator()(const Employee& item)
    {
        static std::hash<std::string> hf;
        return hf(item.getName());
    }    
};
