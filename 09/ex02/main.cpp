#include "PmergeMe.hpp"

#include <iostream>
#include <exception>

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		PmergeMe sorter;
		sorter.run(argc, argv);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}