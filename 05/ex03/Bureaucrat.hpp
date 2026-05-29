#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <exception>

class AForm;

class Bureaucrat
{
	public :
		Bureaucrat();
		Bureaucrat(const std::string& name);
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& other);
		~Bureaucrat();

		Bureaucrat& operator=(const Bureaucrat& other);
		
		const std::string& getName() const;
		int getGrade() const;

		void incrementGrade();
		void decrementGrade();
		void signForm(AForm& form) const;
		void executeForm(const AForm &form) const;

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
		int _grade;
};
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif