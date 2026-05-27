#ifndef PARSELITTERAL_HPP
# define PARSELITTERAL_HPP

# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <cerrno>
# include <climits>
# include <cfloat>
# include <cmath>
# include <limits>

enum LiteralType
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INVALID
};

bool isNan(double value);
bool isInf(double value);
LiteralType detectType(const std::string& literal);
bool parseValue(const std::string& literal, LiteralType type, double& value);


#endif