#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern()
{
	// std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(const Intern& other)
{
	(void)other;
	// std::cout << "Intern copy constructor called" << std::endl;
}

Intern::~Intern()
{
	// std::cout << "Intern destructor called" << std::endl;
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	// std::cout << "Intern copy assignment operator called" << std::endl;
	return *this;
}

AForm* Intern::createShrubberyCreationForm(const std::string& target)
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyRequestForm(const std::string& target)
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialPardonForm(const std::string& target)
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	std::string names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm* (*creators[3])(const std::string&) = {
		&Intern::createShrubberyCreationForm,
		&Intern::createRobotomyRequestForm,
		&Intern::createPresidentialPardonForm
	};

	for (int i = 0; i < 3; i++)
	{
		if (formName == names[i])
		{
			std::cout << "Intern created " << names[i] << std::endl;
			return creators[i](target);
		}
	}

	std::cerr << "Intern couldn't create " << formName
			  << " because this form does not exist"
			  << std::endl;

	return NULL;
}