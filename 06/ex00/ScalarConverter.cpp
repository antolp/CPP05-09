#include "ScalarConverter.hpp"
#include "ParseLitteral.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cfloat>
#include <cmath>
#include <limits>

//OCF
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter::~ScalarConverter() {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return (*this);
}

static void printChar(double value)
{
	std::cout << "char: ";

	if (isNan(value) || isInf(value) || value < 0 || value > 127)
	{
		std::cout << "impossible" << std::endl;
		return;
	}

	char c = static_cast<char>(value);

	if (!std::isprint(c))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << c << "'" << std::endl;
}

static void printInt(double value)
{
	std::cout << "int: ";

	if (isNan(value) || isInf(value) || value < INT_MIN || value > INT_MAX)
	{
		std::cout << "impossible" << std::endl;
		return;
	}

	std::cout << static_cast<int>(value) << std::endl;
}

static void printFloat(double value)
{
	std::cout << "float: ";

	if (isNan(value))
	{
		std::cout << "nanf" << std::endl;
		return;
	}

	if (value == std::numeric_limits<double>::infinity())
	{
		std::cout << "+inff" << std::endl;
		return;
	}

	if (value == -std::numeric_limits<double>::infinity())
	{
		std::cout << "-inff" << std::endl;
		return;
	}

	if (value < -FLT_MAX || value > FLT_MAX)
	{
		std::cout << "impossible" << std::endl;
		return;
	}

	float f = static_cast<float>(value);

	std::cout << f;
	if (std::floor(f) == f)
		std::cout << ".0";
	std::cout << "f" << std::endl;
}

static void printDouble(double value)
{
	std::cout << "double: ";

	if (isNan(value))
	{
		std::cout << "nan" << std::endl;
		return;
	}

	if (value == std::numeric_limits<double>::infinity())
	{
		std::cout << "+inf" << std::endl;
		return;
	}

	if (value == -std::numeric_limits<double>::infinity())
	{
		std::cout << "-inf" << std::endl;
		return;
	}

	std::cout << value;
	if (std::floor(value) == value)
		std::cout << ".0";
	std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
	LiteralType type = detectType(literal);
	double value = 0.0;

	if (type == TYPE_INVALID || !parseValue(literal, type, value))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
