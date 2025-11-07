#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm () : AForm ("PresidentialPardonForm", 25, 5), target("default")
{
}

PresidentialPardonForm::PresidentialPardonForm (const PresidentialPardonForm &other)  : AForm ("PresidentialPardonForm", 25, 5)
{
	*this = other;
}

PresidentialPardonForm &PresidentialPardonForm::operator= (const PresidentialPardonForm &obj)
{
	if (this != &obj)
	{
		PresidentialPardonForm::AForm::operator=(obj);
		this->target = obj.target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm ()
{
}

PresidentialPardonForm::PresidentialPardonForm (const std::string &target) : AForm ("PresidentialPardonForm", 25, 5), target(target)
{
}

void PresidentialPardonForm::executeForm () const
{
	std::cout << this->target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}