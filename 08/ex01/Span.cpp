#include "Span.hpp"
#include <algorithm>
#include <climits>

Span::Span(void) : _maxSize(0), _numbers()
{
}

Span::Span(unsigned int N) : _maxSize(N), _numbers()
{
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers)
{
}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

Span::~Span(void)
{
}

void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw SpanFullException();
	_numbers.push_back(number);
}

//Sort vector using the STL algorithm
//compare each neighbors with each others
unsigned int Span::shortestSpan(void) const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());

	unsigned int shortest = UINT_MAX;

	for (std::size_t i = 1; i < sorted.size(); ++i)
	{
		unsigned int diff =
			sorted[i] - sorted[i - 1];

		if (diff < shortest)
			shortest = diff;
	}

	return shortest;
}

//always largest number - smallest number
unsigned int Span::longestSpan(void) const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int>::const_iterator minIt =
		std::min_element(_numbers.begin(), _numbers.end());

	std::vector<int>::const_iterator maxIt =
		std::max_element(_numbers.begin(), _numbers.end());

	return *maxIt - *minIt;
}

const char* Span::SpanFullException::what(void) const throw()
{
	return "Span is already full";
}

const char* Span::NoSpanException::what(void) const throw()
{
	return "No span can be found (needs at least two integers)";
}