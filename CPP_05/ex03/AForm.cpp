#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm () : name ("Default"), isSigned (0), GradeToSign (20), GradeToExecute (10)
{
}

AForm::AForm (const AForm &other) : name(other.getName()), isSigned (0), GradeToSign (other.getGradeToSign()), GradeToExecute (other.getGradeToExecute())
{
}

AForm &AForm::operator= (const AForm &obj)
{
	if (this != &obj)
		this->isSigned = obj.getIsSigned();
	return *this;
}

AForm::~AForm ()
{
}

AForm::AForm (const std::string &name, int gradetosign, int gradetoexecute) : name (name), isSigned (0), GradeToSign (gradetosign), GradeToExecute (gradetoexecute)
{
	if (this->GradeToSign < 1 || this->GradeToExecute < 1)
		throw GradeTooHighException();
	if (this->GradeToSign > 150 || this->GradeToExecute > 150)
		throw GradeTooLowException();
}

std::string AForm::getName () const
{
	return (this->name);
}
bool AForm::getIsSigned () const
{
	return (this->isSigned);
}

int AForm::getGradeToSign () const
{
	return (this->GradeToSign);
}

int AForm::getGradeToExecute () const
{
	return (this->GradeToExecute);
}

std::ostream &operator<< (std::ostream &out, const AForm &obj)
{
	if (obj.getIsSigned() == 0)
		out << obj.getName() << ", AForm NOT signed, grade to sign : " << obj.getGradeToSign() << ", grade to execute : "\
		 << obj.getGradeToExecute();
	else
		out << obj.getName() << ", AForm signed, grade to sign : " << obj.getGradeToSign() << ", grade to execute : "\
		 << obj.getGradeToExecute();
	return out;
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("AForm: Grade too high!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("AForm: Grade too low!");
}

void AForm::beSigned(const Bureaucrat &obj)
{
	if (obj.getGrade() <= this->GradeToSign)
		this->isSigned = true;
	else
		throw GradeTooLowException();
}

void AForm::execute(Bureaucrat const & executor) const
{
	if (!this->isSigned)
		throw std::runtime_error ("Form is not signed!");
	else if (executor.getGrade() <= this->GradeToExecute)
		this->executeForm();
	else
		throw GradeTooLowException();
}