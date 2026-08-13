#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.hpp"

int main()
{
    std::cout << "\n=== Valid bureaucrat ===" << std::endl;
    try
    {
        Bureaucrat bob("bob", 3);

        std::cout << bob << std::endl;

        bob.incrementGrade();
        std::cout << bob << std::endl;

        bob.incrementGrade();
        std::cout << bob << std::endl;

        std::cout << "(increment too much : )" << std::endl;
        bob.incrementGrade();
        bob.incrementGrade();
        bob.incrementGrade();
        //here should destruct then throw
        std::cout << bob << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Constructor: grade too high ===" << std::endl;
    try
    {
        Bureaucrat invalid("zero", 0);
        std::cout << invalid << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Constructor: grade too low ===" << std::endl;
    try
    {
        Bureaucrat invalid("too low", 151);
        std::cout << invalid << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Increment past grade 1 ===" << std::endl;
    try
    {
        Bureaucrat boss("boss", 1);

        std::cout << boss << std::endl;
        boss.incrementGrade();
        std::cout << boss << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Decrement past grade 150 ===" << std::endl;
    try
    {
        Bureaucrat intern("intern", 150);

        std::cout << intern << std::endl;
        intern.decrementGrade();
        std::cout << intern << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}