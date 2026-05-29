#ifndef AFORM_HPP
# define AFORM_HPP

# include <string>
# include <ostream>
# include <exception>

class Bureaucrat;

class AForm
{
	public:
		AForm();
		AForm(const std::string& name, int gradeToSign, int gradeToExecute);
		AForm(const AForm& other);
		virtual ~AForm();

		AForm& operator=(const AForm& other);

		const std::string& getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		void beSigned(const Bureaucrat& bureaucrat);

		virtual void execute(const Bureaucrat& executor) const = 0;

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

		class FormNotSignedException : public std::exception
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

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif