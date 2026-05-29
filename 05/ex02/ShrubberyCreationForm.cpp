#include "ShrubberyCreationForm.hpp"
#include <iostream>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), _target("default")
{
	// std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
	// std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target)
{
	// std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	// std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	// std::cout << "ShrubberyCreationForm copy assignment operator called" << std::endl;

	if (this != &other)
	{
		AForm::operator=(other);
		this->_target = other._target;
	}

	return *this;
}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
	AForm::execute(executor);

	std::ofstream file((this->_target + "_shrubbery").c_str());

	if (!file)
	{
		std::cerr << "Could not create shrubbery file" << std::endl;
		return;
	}
	file << " * shrubbery * " << std::endl;

}
