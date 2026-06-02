#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <exception>

class Span
{
private:
	unsigned int		_maxSize;
	std::vector<int>	_numbers;

public:
	Span(void);
	Span(unsigned int N);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span(void);

	void addNumber(int number);

	unsigned int shortestSpan(void) const;
	unsigned int longestSpan(void) const;

	//first check the size of what we're tring to add to our Span using std::distance
	//then add it using instert
	template <typename InputIterator>
	void addNumbers(InputIterator begin, InputIterator end)
	{
		typename std::iterator_traits<InputIterator>::difference_type count;

		count = std::distance(begin, end);

		if (count < 0 || _numbers.size() + count > _maxSize)
			throw SpanFullException();

		_numbers.insert(_numbers.end(), begin, end);
	}

	class SpanFullException : public std::exception
	{
	public:
		virtual const char* what(void) const throw();
	};

	class NoSpanException : public std::exception
	{
	public:
		virtual const char* what(void) const throw();
	};
};

#endif