#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <exception>

int main()
{
    std::cout << "\n=== Valid form creation ===" << std::endl;
    try
    {
        Form form("Tax form", 50, 25);
        std::cout << form << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Invalid form: grade too high ===" << std::endl;
    try
    {
        Form form("Impossible", 0, 25);
        std::cout << form << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Invalid form: grade too low ===" << std::endl;
    try
    {
        Form form("Useless form", 50, 151);
        std::cout << form << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Bureaucrat signs successfully ===" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 20);
        Form       form("Important", 50, 25);

        std::cout << boss << std::endl;
        std::cout << form << std::endl;

        boss.signForm(form);

        std::cout << form << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Bureaucrat fails to sign ===" << std::endl;
    try
    {
        Bureaucrat intern("Intern", 100);
        Form       form("Secret", 50, 25);

        std::cout << intern << std::endl;
        std::cout << form << std::endl;

        intern.signForm(form);

        std::cout << form << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}