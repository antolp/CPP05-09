#include "ScalarConverter.hpp"
#include "ParseLitteral.hpp"

bool isNan(double value)
{
	return (value != value);
}

bool isInf(double value)
{
	return (value == std::numeric_limits<double>::infinity()
		|| value == -std::numeric_limits<double>::infinity());
}

static bool isPseudoFloat(const std::string& s)
{
	return (s == "nanf" || s == "+inff" || s == "-inff");
}

static bool isPseudoDouble(const std::string& s)
{
	return (s == "nan" || s == "+inf" || s == "-inf");
}

static bool isIntLiteral(const std::string& s)
{
	size_t i = 0;

	if (s.empty())
		return (false);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (i == s.length())
		return (false);
	while (i < s.length())
	{
		if (!std::isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

//first find digit before dot, then find dot, then find digit after dot
//if there's anything other return false
static bool isDecimalLiteral(const std::string& s)
{
	size_t i = 0;
	bool dot = false;
	bool digitBeforeDot = false;
	bool digitAfterDot = false;

	if (s.empty())
		return (false);
	if (s[i] == '+' || s[i] == '-')
		i++;

	while (i < s.length())
	{
		if (std::isdigit(s[i]))
		{
			if (dot)
				digitAfterDot = true;
			else
				digitBeforeDot = true;
		}
		else if (s[i] == '.' && !dot)
			dot = true;
		else
			return (false);
		i++;
	}
	return (dot && digitBeforeDot && digitAfterDot);
}

//if f at the end, test if decimal without the trailing f
static bool isFloatLiteral(const std::string& s)
{
	if (s.length() < 2 || s[s.length() - 1] != 'f')
		return (false);
	return (isDecimalLiteral(s.substr(0, s.length() - 1)));
}

//
LiteralType detectType(const std::string& literal)
{
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return (TYPE_CHAR);
	if (isPseudoFloat(literal))
		return (TYPE_FLOAT);
	if (isPseudoDouble(literal))
		return (TYPE_DOUBLE);
	if (isIntLiteral(literal))
		return (TYPE_INT);
	if (isFloatLiteral(literal))
		return (TYPE_FLOAT);
	if (isDecimalLiteral(literal))
		return (TYPE_DOUBLE);
	return (TYPE_INVALID);
}

bool parseValue(const std::string& literal, LiteralType type, double& value)
{
	errno = 0;

	if (type == TYPE_CHAR)
	{
		value = static_cast<double>(literal[1]);
		return (true);
	}

	if (literal == "nan" || literal == "nanf")
	{
		value = std::numeric_limits<double>::quiet_NaN();
		return (true);
	}

	if (literal == "+inf" || literal == "+inff")
	{
		value = std::numeric_limits<double>::infinity();
		return (true);
	}

	if (literal == "-inf" || literal == "-inff")
	{
		value = -std::numeric_limits<double>::infinity();
		return (true);
	}

	value = std::strtod(literal.c_str(), NULL);

	if (errno == ERANGE && isInf(value))
		return (false);

	if (type == TYPE_FLOAT)
	{
		if (value < -FLT_MAX || value > FLT_MAX)
			return (false);
		value = static_cast<double>(static_cast<float>(value));
	}

	return (true);
}