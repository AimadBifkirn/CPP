#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm () : AForm ("PresidentialPardonForm", 25, 5)
{
}

PresidentialPardonForm::PresidentialPardonForm (const PresidentialPardonForm &other)  : AForm ("PresidentialPardonForm", 25, 5)
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