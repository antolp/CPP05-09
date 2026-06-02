#include <iostream>
#include <vector>
#include <list>
#include "Span.hpp"

static void printTitle(const std::string& title)
{
	std::cout << "\n=== " << title << " ===" << std::endl;
}

static void printSpans(const Span& sp)
{
	try
	{
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << sp.longestSpan() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

int main()
{
	{
		printTitle("Subject example");

		Span sp(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		printSpans(sp);
	}

	{
		printTitle("Not enough numbers");

		Span empty(5);
		std::cout << "Empty Span:" << std::endl;
		printSpans(empty);

		Span oneNumber(5);
		oneNumber.addNumber(42);
		std::cout << "\nOne-number Span:" << std::endl;
		printSpans(oneNumber);
	}

	{
		printTitle("Too many numbers with addNumber");

		Span sp(3);

		try
		{
			sp.addNumber(1);
			sp.addNumber(2);
			sp.addNumber(3);
			sp.addNumber(4);
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}

		printSpans(sp);
	}

	{
		printTitle("Duplicate numbers");

		Span sp(5);

		sp.addNumber(8);
		sp.addNumber(3);
		sp.addNumber(3);
		sp.addNumber(-10);
		sp.addNumber(42);

		printSpans(sp);
		//Expected:
		//shortest: 0
		//longest:  52
	}

	{
		printTitle("addNumbers with vector iterators");

		std::vector<int> values;

		values.push_back(100);
		values.push_back(40);
		values.push_back(70);
		values.push_back(10);
		values.push_back(130);

		Span sp(5);
		sp.addNumbers(values.begin(), values.end());

		printSpans(sp);
		//Expected:
		//sorted values: 10 40 70 100 130
		//shortest: 30
		//longest:  120
	}

	{
		printTitle("addNumbers with list iterators");

		std::list<int> values;

		values.push_back(100);
		values.push_back(50);
		values.push_back(75);
		values.push_back(25);

		Span sp(4);
		sp.addNumbers(values.begin(), values.end());

		printSpans(sp);
		//Expected:
		//sorted values: 25 50 75 100
		//shortest: 25
		//longest:  75
	}

	{
		printTitle("Too many numbers with addNumbers");

		std::vector<int> values;

		values.push_back(1);
		values.push_back(2);
		values.push_back(3);
		values.push_back(4);

		Span sp(3);

		try
		{
			sp.addNumbers(values.begin(), values.end());
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}

		std::cout << "Trying to fill the Span after failed addNumbers:" << std::endl;

		try
		{
			sp.addNumber(10);
			sp.addNumber(20);
			sp.addNumber(30);
			printSpans(sp);
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	{
		printTitle("More than 10000 numbers");

		const int amount = 12000;
		std::vector<int> values;

		values.reserve(amount);

		for (int i = amount - 1; i >= 0; --i)
			values.push_back(i * 3);

		Span sp(amount);
		sp.addNumbers(values.begin(), values.end());

		printSpans(sp);

		std::cout << "Expected shortest span: 3" << std::endl;
		std::cout << "Expected longest span:  " << (amount - 1) * 3 << std::endl;
	}

	return 0;
}