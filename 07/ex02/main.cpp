#include "Array.hpp"
#include <iostream>
#include <string>
#include <exception>



int main(void)
{
	try
	{
		std::cout << "\n=== " << "Default constructor" << " ===" << std::endl;
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


		std::cout << "\n=== " << "Int array" << " ===" << std::endl;
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


		std::cout << "\n=== " << "Copy constructor (deep copy)"  << " ===" << std::endl;
		Array<int> copy(numbers);
		numbers[0] = 999;
		std::cout << "numbers[0] after modification = " << numbers[0] << std::endl;
		std::cout << "copy[0] should remain old value = " << copy[0] << std::endl;


		std::cout << "\n=== " << "Assignment operator (deep copy)" << " ===" << std::endl;
		Array<int> assigned;
		assigned = numbers;

		numbers[1] = 888;

		std::cout << "numbers[1] after modification = " << numbers[1] << std::endl;
		std::cout << "assigned[1] should remain old value = " << assigned[1] << std::endl;

		std::cout << "\n=== " << "Self-assignment" << " ===" << std::endl;
		assigned = assigned;
		for (unsigned int i = 0; i < assigned.size(); ++i)
			std::cout << "assigned[" << i << "] = " << assigned[i] << std::endl;

		std::cout << "\n=== " << "Const operator[]" << " ===" << std::endl;
		Array<int> constSource(3);
		constSource[0] = 1;
		constSource[1] = 2;
		constSource[2] = 3;

		Array<int> const constArray(constSource);

		std::cout << "constArray[0] = " << constArray[0] << std::endl;
		std::cout << "constArray[1] = " << constArray[1] << std::endl;
		std::cout << "constArray[2] = " << constArray[2] << std::endl;

		//this should not compile :
		// constArray[0] = 42;

		std::cout << "\n=== " << "String array" << " ===" << std::endl;
		Array<std::string> words(3);

		words[0] = "hello";
		words[1] = "template";
		words[2] = "array";

		for (unsigned int i = 0; i < words.size(); ++i)
			std::cout << "words[" << i << "] = " << words[i] << std::endl;

		Array<std::string> wordsCopy(words);

		words[1] = "modified";

		std::cout << "words[1] after modification = " << words[1] << std::endl;
		std::cout << "wordsCopy[1] remains old value = " << wordsCopy[1] << std::endl;

		std::cout << "\n=== " << "Out of bounds" << " ===" << std::endl;
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