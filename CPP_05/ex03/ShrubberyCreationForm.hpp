#pragma once

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	private:
		std::string target;
	public:
		ShrubberyCreationForm ();
		ShrubberyCreationForm (const ShrubberyCreationForm &other);
		ShrubberyCreationForm &operator= (const ShrubberyCreationForm &obj);
		~ShrubberyCreationForm ();

		ShrubberyCreationForm (const std::string &target);
		void executeForm () const;
};