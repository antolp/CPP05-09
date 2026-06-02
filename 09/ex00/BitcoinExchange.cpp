#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->_prices = other._prices;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
}

//trim first and last whitespaces
std::string BitcoinExchange::trim(const std::string &s)
{
	std::size_t start = s.find_first_not_of(" \t");
	std::size_t end;

	if (start == std::string::npos)
		return ("");
	end = s.find_last_not_of(" \t");
	return (s.substr(start, end - start + 1));
}

//leap year divisible by 400 or 4
bool BitcoinExchange::isLeapYear(int year)
{
	if (year % 400 == 0)
		return (true);
	if (year % 100 == 0)
		return (false);
	return (year % 4 == 0);
}

//year valid if it has the right format
//and if each date is coherent
bool BitcoinExchange::isValidDate(const std::string &date)
{
	int month;
	int day;
	int daysInMonth[12] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return (false);
	}

	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12 || day < 1)
		return (false);

	return (day <= daysInMonth[month - 1]);
}

//accept only signs at first then digits and one dot
//then strtod()
bool BitcoinExchange::parseValue(const std::string &s, double &value)
{
	char *end;
	bool hasDigit = false;
	bool hasDot = false;
	std::size_t i = 0;

	if (s.empty())
		return (false);

	if (s[i] == '-' || s[i] == '+')
		++i;

	while (i < s.length())
	{
		if (s[i] >= '0' && s[i] <= '9')
			hasDigit = true;
		else if (s[i] == '.' && !hasDot)
			hasDot = true;
		else
			return (false);
		++i;
	}

	if (!hasDigit)
		return (false);

	value = std::strtod(s.c_str(), &end);
	return (*end == '\0');
}

//iterate and finds date, if no lower bound at found upper date, not date available
double BitcoinExchange::getPriceForDate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it;

	it = this->_prices.lower_bound(date);

	if (it != this->_prices.end() && it->first == date)
		return (it->second);

	if (it == this->_prices.begin())
		throw std::runtime_error("Error: no exchange rate available for this date.");

	--it;
	return (it->second);
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file.is_open())
		throw std::runtime_error("Error: could not open database.");

	while (std::getline(file, line))
	{
		std::size_t comma = line.find(',');
		std::string date;
		std::string priceText;
		double price;

		if (line == "date,exchange_rate")
			continue;

		if (comma == std::string::npos)
			continue;

		date = trim(line.substr(0, comma));
		priceText = trim(line.substr(comma + 1));

		if (isValidDate(date) && parseValue(priceText, price))
			this->_prices[date] = price;
	}
}


void BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream file(filename.c_str());
	std::string line;

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	while (std::getline(file, line))
	{
		std::size_t pipe;
		std::string date;
		std::string valueText;
		double value;
		double price;

		if (line == "date | value")
			continue;

		pipe = line.find('|');

		if (pipe == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		date = trim(line.substr(0, pipe));
		valueText = trim(line.substr(pipe + 1));

		if (!isValidDate(date) || !parseValue(valueText, value))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}

		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		try
		{
			price = getPriceForDate(date);
			std::cout << date << " => " << valueText << " = "
					  << value * price << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}