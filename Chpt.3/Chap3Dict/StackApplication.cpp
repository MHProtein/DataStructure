#include <iostream>
#include <string>
#include <sstream>

#include "StackApplication.h"

#include <vector>
#include "Stack.h"

//Balancing Symbols
void BalacingSymbol(const std::string& str)
{
    Stack<char> stk;
    size_t pos = 0;
    for (const auto& item : str)
    {
        if (item == '(' || item == '[' || item == '{')
        {
            stk.push(item);
        }
        if (item == ')' || item == ']' || item == '}')
        {
            if (stk.empty())
            {
                std::cout << "symbol: " << item << "at position" << ++pos << " mismatching" << std::endl;
                continue;
            }

            char prev_part = stk.top();
            stk.pop();
            if ((prev_part == '(' && item == ')') || (prev_part == '[' && item == ']') || (prev_part == '{' && item ==
                '}'))
                continue;
            std::cout << "symbol: " << item << " at position " << ++pos << " mismatching" << std::endl;
        }
        ++pos;
    }

    if (!stk.empty()) //indicating symbol(s) remaining staying in the stack
    {
        while (!stk.empty())
        {
            std::cout << "symbol: " << stk.top() << " mismatching" << std::endl;
            stk.pop();
        }
    }
}

double ReversePolishNotationCalc(const std::string& expression)
{
    std::vector<std::string> splits;
    auto from = expression.begin();
    for (auto it = expression.begin(); it != expression.end(); ++it)
    {
        std::cout << "debug1" << std::endl;
        if (*it == ' ')
        {
            splits.emplace_back(from, it);
            from = it + 1;
            while (*from == ' ')
            {
                from += 1;
            }
        }
        if (it == expression.end() - 1)
        {
            splits.emplace_back(from, expression.end());
        }
    }

    Stack<double> stk;
    for (const auto& item : splits)
    {
        if (item[0] >= '0' && item[0] <= '9')
        {
            stk.push(std::stod(item));
        }
        else if (item == "+" || item == "-" || item == "*" || item == "/")
        {
            double result = 0;
            double num1 = stk.top();
            stk.pop();
            double num2 = stk.top();
            stk.pop();

            char sign = item[0];
            switch (sign)
            {
            case '+':
                {
                    result = num1 + num2;
                    break;
                }
            case '-':
                {
                    result = num1 - num2;
                    break;
                }
            case '*':
                {
                    result = num1 * num2;
                    break;
                }
            case '/':
                {
                    result = num1 / num2;
                    break;
                }
            default:
                break;
            }
            stk.push(result);
        }
    }
    return stk.top();
}

//Reverse Polish Notation Transform
std::string InfixToPostFix(const std::string& expression)
{
    std::string returnVal;
    std::vector<std::string> split;
    std::stringstream stream(expression);
    std::string temp;
    while (std::getline(stream, temp, ' '))
    {
        split.push_back(temp);
    }

    Stack<Operator> stk;
    for (const auto& item : split)
    {
        if (item[0] >= '0' && item[0] <= '9')
        {
            returnVal += (item + ' ');
        }
        else if (item == "+" || item == "-" || item == "*" || item == "/" || item == "(")
        {
            Operator ope(item[0]);
            if (stk.empty())
            {
                stk.push(ope);
                continue;
            }

            if (ope.precedence > stk.top().precedence)
            {
                stk.push(ope);
            }
            else if (ope.precedence <= stk.top().precedence)
            {
                if (stk.top().op == '(')
                {
                    stk.push(ope);
                    continue;
                }

                while (!stk.empty())
                {
                    if (stk.top().op == '(')
                        break;
                    char temp = stk.top().op;
                    stk.pop();
                    returnVal.push_back(temp);
                    returnVal.push_back(' ');
                }
                stk.push(ope);
            }
        }
        else if (item[0] == ')')
        {
            while (!stk.empty())
            {
                if (stk.top().op == '(')
                    break;
                char temp = stk.top().op;
                stk.pop();
                returnVal.push_back(temp);
                returnVal.push_back(' ');
            }

            if (stk.empty())
            {
                throw std::exception("Wrong expression, missing '(' !");
            }
            stk.pop(); //erase the '('
        }
    }

    while (!stk.empty())
    {
        char temp = stk.top().op;
        stk.pop();
        returnVal.push_back(temp);
        returnVal.push_back(' ');
    }

    while (returnVal.back() == ' ')
        returnVal.pop_back();
    return returnVal;
}
