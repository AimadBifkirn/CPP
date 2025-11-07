#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm () : AForm ("ShrubberyCreationForm", 145, 137), target("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm (const ShrubberyCreationForm &other)  : AForm ("ShrubberyCreationForm", 145, 137)
{
	*this = other;
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

ShrubberyCreationForm::ShrubberyCreationForm (const std::string &target) : AForm ("ShrubberyCreationForm", 145, 137), target(target)
{
}

void ShrubberyCreationForm::executeForm () const
{
	std::ofstream file((this->target + "_shrubbery").c_str());
	if (!file)
	{
	   std::cout << "Error: could not open file.\n";
	   return ;
	}

	file << "	       ccee88oo" << std::endl;
	file << "      C8O8O8Q8PoOb o8oo" << std::endl;
	file << "     dOB69QO8PdUOpugoO9bD" << std::endl;
	file << "    CgggbU8OU qOp qOdoUOdcb" << std::endl;
	file << "      6OuU  /p u gcoUodpP" << std::endl;
	file << "         \\///  /douUP" << std::endl;
	file << "           ///////" << std::endl;
	file << "             |||/" << std::endl;
	file << "             |||\\" << std::endl;
	file << "            |||||" << std::endl;
	file << "       ....//||||//...." << std::endl;
	file.close();
}