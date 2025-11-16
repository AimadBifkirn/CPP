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
		virtual ~AForm ();

		AForm (const std::string &name, int gradetosign, int gradetoexecute);
		const std::string &getName() const;
		const bool &getIsSigned() const;
		const int &getGradeToSign() const;
		const int &getGradeToExecute() const;
		void  beSigned(const Bureaucrat &obj);

		void execute(Bureaucrat const & executor) const;
		virtual void executeForm () const = 0;

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