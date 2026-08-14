#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

static void checkGrade(int grade)
{
	if (grade < 1)
		throw AForm::GradeTooHighException();
	if (grade > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm()
	: _name("Unknown"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	// std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	// std::cout << "AForm constructor called" << std::endl;

	checkGrade(_gradeToSign);
	checkGrade(_gradeToExecute);
}

AForm::AForm(const AForm& other)
	: _name(other._name),
	  _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign),
	  _gradeToExecute(other._gradeToExecute)
{
	// std::cout << "AForm copy constructor called" << std::endl;
}

AForm::~AForm()
{
	// std::cout << "AForm destructor called" << std::endl;
}

AForm& AForm::operator=(const AForm& other)
{
	// std::cout << "AForm copy assignment operator called" << std::endl;

	if (this != &other)
		this->_isSigned = other._isSigned;

	return *this;
}

const std::string& AForm::getName() const
{
	return this->_name;
}

bool AForm::getIsSigned() const
{
	return this->_isSigned;
}

int AForm::getGradeToSign() const
{
	return this->_gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return this->_gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();

	this->_isSigned = true;
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "grade is too low";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "form is not signed";
}

std::ostream& operator<<(std::ostream& os, const AForm& form)
{
	os << "Form: " << form.getName()
	   << ", signed: " << (form.getIsSigned() ? "yes" : "no")
	   << ", grade required to sign: " << form.getGradeToSign()
	   << ", grade required to execute: " << form.getGradeToExecute();

	return os;
}