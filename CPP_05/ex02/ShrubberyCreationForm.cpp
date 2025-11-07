#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm () : AForm ("PresidentialPardonForm", 145, 137)
{
}

PresidentialPardonForm::PresidentialPardonForm (const PresidentialPardonForm &other)  : AForm ("PresidentialPardonForm", 145, 137)
{
}

PresidentialPardonForm &PresidentialPardonForm::operator= (const PresidentialPardonForm &obj)
{
	if (this != &obj)
	{
		PresidentialPardonForm::AForm::operator=(obj);
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm ()
{
}