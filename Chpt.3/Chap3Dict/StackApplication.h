#include <string>

void BalacingSymbol(const std::string& str);

double ReversePolishNotationCalc(const std::string& expression);

std::string InfixToPostFix(const std::string& expression);

struct Operator
{
    Operator(): op(0), precedence(0)
    {
    }

    Operator(const char& Op): op(Op)
    {
        SetPrecedence();
    }

    Operator(char&& Op) noexcept : op(std::move(Op))
    {
        SetPrecedence();
    }

    void SetPrecedence()
    {
        if (op == '+' || op == '-')
            precedence = 1;
        else if (op == '*' || op == '/')
            precedence = 2;
        else if (op == '(')
            precedence = 3;
    }

    char op;
    size_t precedence;
};
