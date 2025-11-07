#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm () : AForm ("ShrubberyCreationForm", 145, 137), target("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm (const ShrubberyCreationForm &other)  : AForm ("ShrubberyCreationForm", 145, 137), target("default")
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator= (const ShrubberyCreationForm &obj)
{
	if (this != &obj)
	{
		ShrubberyCreationForm::AForm::operator=(obj);
		this->target = obj.target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm ()
{
}

ShrubberyCreationForm::ShrubberyCreationForm (const std::string &target) : AForm ("ShrubberyCreationForm", 25, 5), target(target)
{
}

void ShrubberyCreationForm::executeForm () const
{
	std::ofstream file(this->target + "_shrubbery");
	if (!file)
	{
	   std::cout << "Error: could not open file.\n";
	   return ;
	}

	file << "	       ccee88oo";
	file << "      C8O8O8Q8PoOb o8oo";
	file << "     dOB69QO8PdUOpugoO9bD";
	file << "    CgggbU8OU qOp qOdoUOdcb";
	file << "      6OuU  /p u gcoUodpP";
	file << "         \\\//  /douUP";
	file << "           \/////";
	file << "             |||/";
	file << "             |||\/";
	file << "            |||||";
	file << "       .....//||||\....";
	file.close();
}