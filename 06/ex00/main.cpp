#include "ScalarConverter.hpp"

#include <iostream>
#include <limits>

// 42        // integer literal
// 'a'       // character literal
// 4.2f      // float literal
// 4.2       // double literal
// "hello"   // string literal

static void printTest(const std::string& literal)
{
	std::cout << "\n\tScalarConverter::convert(\"" << literal << "\")" << std::endl;
	ScalarConverter::convert(literal);
}

void tests()
{
	std::cout << " === " << "subject tests" << " ===" << std::endl;
	printTest("0");
	printTest("nan");
	printTest("42.0f");

	std::cout << "\n === " << "classic types" << " ===" << std::endl;
	printTest("100");
	printTest("4.2f");
	printTest("4.2");
	printTest("a");
	printTest("'a'");
	printTest("'\n'");

	std::cout << "\n === " << "weird decimal edge cases" << " ===" << std::endl;
	printTest("0.f");
	printTest(".0f");
	printTest("42.f");
	printTest(".42f");
	printTest("0.");
	printTest(".0");

	std::cout << "\n === " << "limits" << " ===" << std::endl;
	printTest("31");
	printTest("32");
	printTest("126");
	printTest("127");
	printTest("2147483647");	// int max
	printTest("2147483648");	// int overflow
	printTest("-2147483648");	// int min
	printTest("-2147483649");	// int underflow
	printTest("400000000000000000000000000000000000000.0f");	//float overflow
	printTest("-400000000000000000000000000000000000000.0f");	//float underflow


	std::cout << "\n === " << "pseudo-literals and invalid" << " ===" << std::endl;
	printTest("nanf");
	printTest("+inf");
	printTest("-inff");
	printTest("42ff");
	printTest(".f");
	printTest("abc");

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

	tests();

	std::cout << argv[1] << std::endl;
	ScalarConverter::convert(argv[1]);
	return 0;
}