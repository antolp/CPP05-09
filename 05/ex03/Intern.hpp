#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>

class AForm;

class Intern
{
	public:
		Intern();
		Intern(const Intern& other);
		~Intern();

		Intern& operator=(const Intern& other);

		AForm* makeForm(const std::string& formName, const std::string& target) const;

	private:
		static AForm* createShrubberyCreationForm(const std::string& target);
		static AForm* createRobotomyRequestForm(const std::string& target);
		static AForm* createPresidentialPardonForm(const std::string& target);
};

#endif