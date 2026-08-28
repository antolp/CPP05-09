#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_deque = other._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
}

void PmergeMe::run(int argc, char **argv)
{
	clock_t startVector;
	clock_t endVector;
	clock_t startDeque;
	clock_t endDeque;
	double vectorTime;
	double dequeTime;

	this->parseInput(argc, argv);

	this->printBefore();

	startVector = std::clock();
	this->sortVector();
	endVector = std::clock();

	startDeque = std::clock();
	this->sortDeque();
	endDeque = std::clock();

	this->printAfter();

	vectorTime = PmergeMe::getElapsedMicroseconds(startVector, endVector);
	dequeTime = PmergeMe::getElapsedMicroseconds(startDeque, endDeque);

	std::cout << "Time to process a range of "
			  << this->_vector.size()
			  << " elements with std::vector : "
			  << vectorTime
			  << " us"
			  << std::endl;

	std::cout << "Time to process a range of "
			  << this->_deque.size()
			  << " elements with std::deque : "
			  << dequeTime
			  << " us"
			  << std::endl;
}

void PmergeMe::parseInput(int argc, char **argv)
{
	int value;

	if (argc < 2)
		throw std::runtime_error("Error");

	for (int i = 1; i < argc; ++i)
	{
		value = PmergeMe::parsePositiveInt(argv[i]);
		this->_vector.push_back(value);
		this->_deque.push_back(value);
	}
}

int PmergeMe::parsePositiveInt(const std::string &s)
{
	char *endptr;
	long value;

	if (s.empty())
		throw std::runtime_error("Error");

	for (std::size_t i = 0; i < s.size(); ++i)
	{
		if (!std::isdigit(s[i]))
			throw std::runtime_error("Error");
	}

	value = std::strtol(s.c_str(), &endptr, 10);

	if (*endptr != '\0')
		throw std::runtime_error("Error");

	if (value <= 0 || value > INT_MAX)
		throw std::runtime_error("Error");

	return (static_cast<int>(value));
}

void PmergeMe::printBefore(void) const
{
	std::cout << "Before:";

	for (std::vector<int>::const_iterator it = this->_vector.begin();
		 it != this->_vector.end();
		 ++it)
	{
		std::cout << " " << *it;
	}

	std::cout << std::endl;
}

void PmergeMe::printAfter(void) const
{
	std::cout << "After:";

	for (std::vector<int>::const_iterator it = this->_vector.begin();
		 it != this->_vector.end();
		 ++it)
	{
		std::cout << " " << *it;
	}

	std::cout << std::endl;
}

double PmergeMe::getElapsedMicroseconds(clock_t start, clock_t end)
{
	return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

void PmergeMe::sortVector(void)
{
	//vector Ford-Johnson implementation.
}

void PmergeMe::sortDeque(void)
{
	//deque Ford-Johnson implementation.
}