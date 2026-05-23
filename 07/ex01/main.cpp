#include "iter.hpp"
#include <iostream>

template< typename T >
void print( T const & x )
{
    std::cout << x << std::endl;
    return;
}

template <typename T>
void printAddress(T const& x)
{
	std::cout << &x << std::endl;
}

template <typename T>
void increment(T &x)
{
	x++;
}

void addCoucou(std::string& s)
{
	s += " coucou";
}

int main()
{
    int tab[] = { 0, 1, 2, 3, 4 };
	std::string tab2[3] = {
		"hello",
		"templates",
		"world"
	};

    iter(tab, 5, print);
    iter(tab, 5, increment);
    iter(tab, 5, print);
    iter(tab2, 3, print);
	iter(tab2, 3, addCoucou);
    iter(tab2, 3, print);
	iter(tab, 5, printAddress);
    return 0;
}