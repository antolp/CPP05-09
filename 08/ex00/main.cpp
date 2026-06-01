#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
#include "easyfind.hpp"

template <typename Container>
void testContainer(Container& container, int value, const std::string& testTitle)
{
	std::cout << testTitle << std::endl;

	typename Container::iterator it = easyfind(container, value);

	if (it == container.end())
	{
		std::cout << "Could not find " << value << std::endl;
	}
	else
	{
		std::cout << "Found " << value << ": " << *it;
		std::cout << " at position " << std::distance(container.begin(), it) << std::endl;
	}
}

int main()
{
	{
		std::cout << "\n\t=== Vector ===" << std::endl;
		std::vector<int> numbers;

		numbers.push_back(10);
		numbers.push_back(20);
		numbers.push_back(30);
		numbers.push_back(20);
		numbers.push_back(40);

		testContainer(numbers, 30, "value exists:");
		testContainer(numbers, 99, "value does not exist:");
		testContainer(numbers, 20, "duplicate value:");
	}

	{
		std::cout << "\n\t=== List ===" << std::endl;
		std::list<int> numbers;

		numbers.push_back(-5);
		numbers.push_back(0);
		numbers.push_back(42);
		numbers.push_back(100);

		testContainer(numbers, 42, "value exists:");
		testContainer(numbers, 7, "value does not exist:");
	}

	{
		std::cout << "\n\t=== Deque ===" << std::endl;
		std::deque<int> numbers;

		numbers.push_back(1);
		numbers.push_back(2);
		numbers.push_back(3);

		testContainer(numbers, 1, "first element:");
		testContainer(numbers, 3, "last element:");
		testContainer(numbers, 4, "value does not exist:");
	}

	{
		std::cout << "\n\t=== Empty vector ===" << std::endl;
		std::vector<int> empty;

		testContainer(empty, 10, "empty container:");
	}

	return 0;
}