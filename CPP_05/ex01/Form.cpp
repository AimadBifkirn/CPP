#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form () : name ("Default"), isSigned (0), GradeToSign (20), GradeToExecute (10)
{
}

Form::Form (const Form &other) : name(other.getName()), isSigned (0), GradeToSign (other.getGradeToSign()), GradeToExecute (other.getGradeToExecute())
{
}

Form &Form::operator= (const Form &obj)
{
	if (this != &obj)
		this->isSigned = obj.getIsSigned();
	return *this;
}

Form::~Form ()
{
}

Form::Form (const std::string &name, int gradetosign, int gradetoexecute) : name (name), isSigned (0), GradeToSign (gradetosign), GradeToExecute (gradetoexecute)
{
	if (this->GradeToSign < 1 || this->GradeToExecute < 1)
		throw GradeTooHighException();
	if (this->GradeToSign > 150 || this->GradeToExecute > 150)
		throw GradeTooLowException();
}

const std::string &Form::getName () const
{
	return (this->name);
}

const bool &Form::getIsSigned () const
{
	return (this->isSigned);
}

const int &Form::getGradeToSign () const
{
	return (this->GradeToSign);
}

const int &Form::getGradeToExecute () const
{
	return (this->GradeToExecute);
}

std::ostream &operator<< (std::ostream &out, const Form &obj)
{
	if (obj.getIsSigned() == 0)
		out << obj.getName() << ", Form NOT signed, grade to sign : " << obj.getGradeToSign() << ", grade to execute : "\
		 << obj.getGradeToExecute();
	else
		out << obj.getName() << ", Form signed, grade to sign : " << obj.getGradeToSign() << ", grade to execute : "\
		 << obj.getGradeToExecute();
	return out;
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Form: Grade too high!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Form: Grade too low!");
}

void Form::beSigned(const Bureaucrat &obj)
{
	if (obj.getGrade() <= this->GradeToSign)
		this->isSigned = 1;
	else
		throw GradeTooLowException();
}
