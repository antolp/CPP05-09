#ifndef FORM_HPP
# define FORM_HPP

# include <string>
# include <ostream>
# include <exception>

class Bureaucrat;

class Form
{
	public:
		Form();
		Form(const std::string& name, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		~Form();

		Form& operator=(const Form& other);

		const std::string& getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		void beSigned(const Bureaucrat& bureaucrat);

		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

	private:
		const std::string _name;
		bool _isSigned;
		const int _gradeToSign;
		const int _gradeToExecute;
};

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif