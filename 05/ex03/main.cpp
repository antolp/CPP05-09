#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>

static void printTitle(const std::string& title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main()
{
    std::srand(std::time(NULL));

    Intern      intern;
    Bureaucrat  boss("Boss", 1);
    Bureaucrat  weak("Weak", 150);
    AForm*      form;

    printTitle("Create shrubbery form");
    form = intern.makeForm("shrubbery creation", "home");
    if (form)
    {
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;
    }

    printTitle("Create robotomy form");
    form = intern.makeForm("robotomy request", "Bender");
    if (form)
    {
        boss.signForm(*form);
        boss.executeForm(*form);
        boss.executeForm(*form);
        boss.executeForm(*form);
        delete form;
    }

    printTitle("Create presidential pardon form");
    form = intern.makeForm("presidential pardon", "Arthur Dent");
    if (form)
    {
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;
    }

    printTitle("Unknown form name");
    form = intern.makeForm("coffee request", "Bob");
    if (form)
    {
        delete form;
    }

    printTitle("Intern creates form, weak bureaucrat fails");
    form = intern.makeForm("presidential pardon", "Ford Prefect");
    if (form)
    {
        weak.signForm(*form);
        weak.executeForm(*form);
        delete form;
    }

    return 0;
}