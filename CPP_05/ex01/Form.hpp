#pragma once

#include <iostream>

class Bureaucrat;

class Form
{
	private:
		const std::string name;
		bool isSigned;
		const int GradeToSign;
		const int GradeToExecute;
	public:

		Form ();
		Form (const Form &other);
		Form &operator= (const Form &obj);
		~Form ();

		Form (const std::string &name, int gradetosign = 20, int gradetoexecute = 10);
		const std::string &getName() const;
		const bool &getIsSigned() const;
		const int &getGradeToSign() const;
		const int &getGradeToExecute() const;
		void  beSigned(const Bureaucrat &obj);

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

std::ostream &operator<< (std::ostream &out, const Form &obj);