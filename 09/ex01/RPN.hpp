#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <list>
#include <stack>

class RPN
{
public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    long evaluate(const std::string& expression);

private:
    std::list<long> _values;
	
    bool isNumber(const std::string& token) const;
    bool isOperator(const std::string& token) const;
    void applyOperator(const std::string& op);
};

#endif