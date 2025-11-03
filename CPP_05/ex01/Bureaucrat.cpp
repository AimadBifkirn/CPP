#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat () : name ("Default"), grade (150)
{
}

Bureaucrat::Bureaucrat (const Bureaucrat &other): name(other.name + "-copy")
{
	*this = other;
}

Bureaucrat &Bureaucrat::operator= (const Bureaucrat &obj)
{
	if (this != &obj)
	{
		this->grade = obj.grade;
	}
	return (*this);
}

Bureaucrat::~Bureaucrat ()
{
}

Bureaucrat::Bureaucrat (const std::string &name, int grade) : name (name)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	this->grade = grade;	
}

const std::string &Bureaucrat::getName () const
{
	return (this->name);
}

int Bureaucrat::getGrade () const
{
	return (this->grade);
}

void Bureaucrat::increment ()
{
	this->grade--;
	if (this->grade < 1)
		throw GradeTooHighException();
}

void Bureaucrat::decrement ()
{
	this->grade++;
	if (this->grade > 150)
		throw GradeTooLowException();
}

std::ostream &operator<< (std::ostream &out, const Bureaucrat &obj)
{
	out << obj.getName() << ", bureaucrat grade " << obj.getGrade() << std::endl;
	return out;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}

void Bureaucrat::signForm(Form &obj)
{
	try
	{
		obj.beSigned(*this);
		std::cout << this->name << " signed " << obj.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << this->getName() << " couldn’t sign " << obj.getName() << " because " << e.what() << '\n';
	}
}