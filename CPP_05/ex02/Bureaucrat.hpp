#pragma once

#include <iostream>
#include <exception>

class AForm;

class Bureaucrat
{
	private:
		const std::string name;
		int   grade;
	public:
		
		Bureaucrat ();
		Bureaucrat (const Bureaucrat &other);
		Bureaucrat &operator= (const Bureaucrat &obj);
		~Bureaucrat ();
		
		Bureaucrat (const std::string& name, int grade = 150);
		const std::string &getName() const;
		int getGrade() const;
		void increment();
		void decrement();

		void signForm(AForm &obj);

		void executeForm(AForm const & form) const;

		class GradeTooHighException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char *what() const throw();
		};
};

std::ostream &operator<< (std::ostream &out ,const Bureaucrat &obj);