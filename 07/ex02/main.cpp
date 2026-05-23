#include <iostream>
#include "Array.hpp"

// int main()
// {
// 	Array<int> empty;
// 	Array<int> numbers(3);

// 	numbers[0] = 42;
// 	numbers[1] = 21;

// 	std::cout << "size: " << numbers.size() << std::endl;
// 	std::cout << numbers[0] << std::endl;

// 	const Array<int> copy(numbers);
// 	std::cout << copy[1] << std::endl;

// 	try
// 	{
// 		std::cout << numbers[10] << std::endl;
// 	}
// 	catch (const std::exception& e)
// 	{
// 		std::cout << "Exception: " << e.what() << std::endl;
// 	}

// 	return 0;
// }


#include "Array.hpp"
#include <iostream>
#include <string>
#include <exception>

static void printTitle(std::string const& title)
{
	std::cout << "\n=== " << title << " ===" << std::endl;
}

int main(void)
{
	try
	{
		printTitle("Default constructor");

		Array<int> empty;
		std::cout << "empty.size() = " << empty.size() << std::endl;

		try
		{
			std::cout << empty[0] << std::endl;
		}
		catch (std::exception const& e)
		{
			std::cout << "Accessing empty[0]: " << e.what() << std::endl;
		}

		printTitle("Int array");

		Array<int> numbers(5);

		std::cout << "numbers.size() = " << numbers.size() << std::endl;

		std::cout << "Default initialized values:" << std::endl;
		for (unsigned int i = 0; i < numbers.size(); ++i)
			std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;

		for (unsigned int i = 0; i < numbers.size(); ++i)
			numbers[i] = static_cast<int>((i + 1) * 10);

		std::cout << "After assigning values:" << std::endl;
		for (unsigned int i = 0; i < numbers.size(); ++i)
			std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;

		printTitle("Copy constructor / deep copy");

		Array<int> copy(numbers);

		numbers[0] = 999;

		std::cout << "numbers[0] after modification = " << numbers[0] << std::endl;
		std::cout << "copy[0] should remain old value = " << copy[0] << std::endl;

		printTitle("Assignment operator / deep copy");

		Array<int> assigned;
		assigned = numbers;

		numbers[1] = 888;

		std::cout << "numbers[1] after modification = " << numbers[1] << std::endl;
		std::cout << "assigned[1] should remain old value = " << assigned[1] << std::endl;

		printTitle("Self-assignment");

		assigned = assigned;

		for (unsigned int i = 0; i < assigned.size(); ++i)
			std::cout << "assigned[" << i << "] = " << assigned[i] << std::endl;

		printTitle("Const operator[]");

		Array<int> constSource(3);
		constSource[0] = 1;
		constSource[1] = 2;
		constSource[2] = 3;

		Array<int> const constArray(constSource);

		std::cout << "constArray[0] = " << constArray[0] << std::endl;
		std::cout << "constArray[1] = " << constArray[1] << std::endl;
		std::cout << "constArray[2] = " << constArray[2] << std::endl;

		// This should NOT compile, which is good:
		// constArray[0] = 42;

		printTitle("String array");

		Array<std::string> words(3);

		words[0] = "hello";
		words[1] = "template";
		words[2] = "array";

		for (unsigned int i = 0; i < words.size(); ++i)
			std::cout << "words[" << i << "] = " << words[i] << std::endl;

		Array<std::string> wordsCopy(words);

		words[1] = "modified";

		std::cout << "words[1] after modification = " << words[1] << std::endl;
		std::cout << "wordsCopy[1] should remain old value = " << wordsCopy[1] << std::endl;

		printTitle("Out of bounds");

		try
		{
			std::cout << numbers[999] << std::endl;
		}
		catch (std::exception const& e)
		{
			std::cout << "Accessing numbers[999]: " << e.what() << std::endl;
		}

		try
		{
			std::cout << words[3] << std::endl;
		}
		catch (std::exception const& e)
		{
			std::cout << "Accessing words[3]: " << e.what() << std::endl;
		}
	}
	catch (std::exception const& e)
	{
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}