#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <exception>

static void printTitle(const std::string& title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main()
{
    printTitle("Create concrete forms");
    try
    {
        ShrubberyCreationForm shrub("home");
        RobotomyRequestForm robot("Clanck");
        PresidentialPardonForm pardon("Michel");

        std::cout << shrub << std::endl;
        std::cout << robot << std::endl;
        std::cout << pardon << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    printTitle("Execute unsigned form");
    try
    {
        Bureaucrat boss("Boss", 1);
        ShrubberyCreationForm shrub("garden");

        boss.executeForm(shrub);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    printTitle("Sign too low");
    try
    {
        Bureaucrat weak("Weak bureaucrat", 150);
        ShrubberyCreationForm shrub("park");

        weak.signForm(shrub);
        std::cout << shrub << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    printTitle("Execute with grade too low");
    try
    {
        Bureaucrat signer("Signer", 1);
        Bureaucrat executor("Executor", 150);
        ShrubberyCreationForm shrub("forest");

        signer.signForm(shrub);
        executor.executeForm(shrub);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    printTitle("shrubbery success");
    try
    {
        Bureaucrat boss("Boss", 1);
        ShrubberyCreationForm shrub("home");

        boss.signForm(shrub);
        boss.executeForm(shrub);
        std::cout << "Check if file home_shrubbery was created." << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    printTitle("Robotomy 1/2 failure");
    try
    {
        Bureaucrat boss("Boss", 1);
        RobotomyRequestForm robot("Bender");

        boss.signForm(robot);

        for (int i = 0; i < 5; ++i)
            boss.executeForm(robot);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    printTitle("Presidential pardon success");
    try
    {
        Bureaucrat president("President", 1);
        PresidentialPardonForm pardon("Arthur Dent");

        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    printTitle("AForm");
    try
    {
        Bureaucrat boss("Boss", 1);

        AForm* forms[3];

        forms[0] = new ShrubberyCreationForm("office");
        forms[1] = new RobotomyRequestForm("Marvin");
        forms[2] = new PresidentialPardonForm("Ford Prefect");

        for (int i = 0; i < 3; ++i)
        {
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
            delete forms[i];
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}