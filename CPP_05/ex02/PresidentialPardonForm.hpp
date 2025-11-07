#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		std::string target;
	public:
		PresidentialPardonForm ();
		PresidentialPardonForm (const PresidentialPardonForm &other);
		PresidentialPardonForm &operator= (const PresidentialPardonForm &obj);
		~PresidentialPardonForm ();

		PresidentialPardonForm (const std::string &target);
		void executeForm () const;
};