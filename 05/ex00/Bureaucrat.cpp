#include <Bureaucrat.hpp>
#include <iostream>
#include <string>

void checkGrade(int grade)
{
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
}

// Default constructor
Bureaucrat::Bureaucrat() : _name("noname"), _grade(150)
{
	std::cout << "Default constructor called\n";
	checkGrade(_grade);
}

Bureaucrat::Bureaucrat(const std::string& name)
	: _name(name), _grade(150)
{
	std::cout << "Name constructor called" << std::endl;
	checkGrade(_grade);
}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
	: _name(name), _grade(grade)
{
	std::cout << "Full constructor called" << std::endl;
	checkGrade(_grade);
}

// Copy constructor
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade)
{
	std::cout << "Copy constructor called\n";
}

// Copy assignment operator
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	std::cout << "Copy assignment operator called\n";
	if (this != &other)
	{
		this->_grade = other._grade;
	}
	return *this;
}

// Destructor
Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called\n";
}

int Bureaucrat::getGrade() const
{
	return this->_grade;
}

const std::string& Bureaucrat::getName() const
{
	return this->_name;
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName()
	   << ", bureaucrat grade "
	   << bureaucrat.getGrade();

	return os;
}

void Bureaucrat::incrementGrade()
{
	checkGrade(this->_grade - 1);
	this->_grade--;
}

void Bureaucrat::decrementGrade()
{
	checkGrade(this->_grade + 1);
	this->_grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "grade is too low";
}
