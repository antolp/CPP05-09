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
	file << "                     .o00o " << std::endl;
	file << "                   o000000oo " << std::endl;
	file << "                  00000000000o " << std::endl;
	file << "                 00000000000000 " << std::endl;
	file << "              oooooo  00000000  o88o " << std::endl;
	file << "           ooOOOOOOOoo  ```''  888888 " << std::endl;
	file << "         OOOOOOOOOOOO'.qQQQQq. `8888' " << std::endl;
	file << "        oOOOOOOOOOO'.QQQQQQQQQQ/.88' " << std::endl;
	file << "        OOOOOOOOOO'.QQQQQQQQQQ/ /q " << std::endl;
	file << "         OOOOOOOOO QQQQQQQQQQ/ /QQ " << std::endl;
	file << "           OOOOOOOOO `QQQQQQ/ /QQ' " << std::endl;
	file << "             OO:F_P:O `QQQ/  /Q' " << std::endl;
	file << "                \\. \\ |  // | " << std::endl;
	file << "                d\\ \\\\|_//// " << std::endl;
	file << "                qP| \\ _' `|Ob " << std::endl;
	file << "                   \\  / \\  \\Op " << std::endl;
	file << "                   |  | O| | " << std::endl;
	file << "           _       /\\. \\_/ /\\ " << std::endl;
	file << "            `---__/|_\\   //|  __ " << std::endl;
	file << "                  `-'  `-'`-'-' " << std::endl;
	file << "tree ascii art from ascii.co.uk " << std::endl;
}
