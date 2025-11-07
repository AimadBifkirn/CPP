#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	public:
		PresidentialPardonForm ();
		PresidentialPardonForm (const PresidentialPardonForm &other);
		PresidentialPardonForm &operator= (const PresidentialPardonForm &obj);
		~PresidentialPardonForm ();
};