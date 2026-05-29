#include "Form.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

static void checkGrade(int grade)
{
	if (grade < 1)
		throw Form::GradeTooHighException();
	if (grade > 150)
		throw Form::GradeTooLowException();
}

Form::Form()
	: _name("Unknown"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	checkGrade(_gradeToSign);
	checkGrade(_gradeToExecute);

	std::cout << "Form constructor called" << std::endl;
}

Form::Form(const Form& other)
	: _name(other._name),
	  _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign),
	  _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Form copy constructor called" << std::endl;
}

Form::~Form()
{
	std::cout << "Form destructor called" << std::endl;
}

Form& Form::operator=(const Form& other)
{
	std::cout << "Form copy assignment operator called" << std::endl;

	if (this != &other)
	{
		this->_isSigned = other._isSigned;
	}

	return *this;
}

const std::string& Form::getName() const
{
	return this->_name;
}

bool Form::getIsSigned() const
{
	return this->_isSigned;
}

int Form::getGradeToSign() const
{
	return this->_gradeToSign;
}

int Form::getGradeToExecute() const
{
	return this->_gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw Form::GradeTooLowException();

	this->_isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "grade is too low";
}

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << "Form: " << form.getName()
	   << ", signed: " << (form.getIsSigned() ? "yes" : "no")
	   << ", grade required to sign: " << form.getGradeToSign()
	   << ", grade required to execute: " << form.getGradeToExecute();

	return os;
}