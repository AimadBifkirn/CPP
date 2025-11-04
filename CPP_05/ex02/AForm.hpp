#pragma once

#include <iostream>

class Bureaucrat;

class  AForm
{
	private:
		const std::string name;
		bool isSigned;
		const int GradeToSign;
		const int GradeToExecute;
	public:

		AForm ();
		AForm (const AForm &other);
		AForm &operator= (const AForm &obj);
		~AForm ();

		AForm (const std::string &name, int gradetosign = 20, int gradetoexecute = 10);
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

std::ostream &operator<< (std::ostream &out, const AForm &obj);