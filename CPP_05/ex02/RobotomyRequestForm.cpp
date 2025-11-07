#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm () : AForm ("RobotomyRequestForm", 25, 5)
{
}

RobotomyRequestForm::RobotomyRequestForm (const RobotomyRequestForm &other)  : AForm ("RobotomyRequestForm", 25, 5)
{
}

RobotomyRequestForm &RobotomyRequestForm::operator= (const RobotomyRequestForm &obj)
{
	if (this != &obj)
	{
		RobotomyRequestForm::AForm::operator=(obj);
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm ()
{
}