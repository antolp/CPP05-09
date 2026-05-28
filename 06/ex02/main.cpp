#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Base.hpp"

int main()
{
    std::srand(std::time(NULL));

    for (int i = 0; i < 10; ++i)
    {
        Base* ptr = generate();

        std::cout << "Pointer identify:   ";
        identify(ptr);

        std::cout << "Reference identify: ";
        identify(*ptr);

        std::cout << std::endl;

        delete ptr;
    }

    return 0;
}