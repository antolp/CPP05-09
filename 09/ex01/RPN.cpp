#include "RPN.hpp"

#include <sstream>
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
    *this = other;
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        this->_values = other._values;
    return *this;
}

RPN::~RPN()
{
}

bool RPN::isNumber(const std::string& token) const
{
    return token.length() == 1 && token[0] >= '0' && token[0] <= '9';
}

bool RPN::isOperator(const std::string& token) const
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

void RPN::applyOperator(const std::string& op)
{
    if (_values.size() < 2)
        throw std::runtime_error("Error");

    long b = _values.back();
    _values.pop_back();

    long a = _values.back();
    _values.pop_back();

    if (op == "+")
        _values.push_back(a + b);
    else if (op == "-")
        _values.push_back(a - b);
    else if (op == "*")
        _values.push_back(a * b);
    else if (op == "/")
    {
        if (b == 0)
            throw std::runtime_error("Error");
        _values.push_back(a / b);
    }
}

long RPN::evaluate(const std::string& expression)
{
    _values.clear();

    std::stringstream ss(expression);
    std::string token;

    while (ss >> token)
    {
        if (isNumber(token))
            _values.push_back(token[0] - '0');
        else if (isOperator(token))
            applyOperator(token);
        else
            throw std::runtime_error("Error");
    }

    if (_values.size() != 1)
        throw std::runtime_error("Error");

    return _values.back();
}