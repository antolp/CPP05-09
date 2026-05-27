#include "ScalarConverter.hpp"

#include <iostream>

// 42        // integer literal
// 'a'       // character literal
// 4.2f      // float literal
// 4.2       // double literal
// "hello"   // string literal

static void printTest(const std::string& literal)
{
	std::cout << "\n>>> ScalarConverter::convert(\"" << literal << "\")" << std::endl;
	ScalarConverter::convert(literal);
}

void tests()
{
	std::cout << " === " << "Classic types" << " ===" << std::endl;
	printTest("100");
	printTest("4.2f");
	printTest("4.2");
	printTest("a");
	printTest("'a'");

	std::cout << "\n === " << "Limits / tricky cases" << " ===" << std::endl;
	printTest("0");
	printTest("31");
	printTest("32");
	printTest("2147483647");
	printTest("2147483648");    // int overflow
	printTest("-2147483648");   // int min
	printTest("-2147483649");

	std::cout << "\n === " << "Pseudo-literals / invalid" << " ===" << std::endl;
	printTest("nan");
	printTest("nanf");
	printTest("+inf");
	printTest("-inff");
	printTest("'\n'");

	std::cout << std::endl;
	return ;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./convert <literal>" << std::endl;
		return 1;
	}

	// tests();
	std::cout << argv[1] << std::endl;
	ScalarConverter::convert(argv[1]);

	return 0;
}