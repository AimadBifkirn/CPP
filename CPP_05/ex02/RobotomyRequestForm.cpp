#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm () : AForm ("RobotomyRequestForm", 72, 45)
{
}

RobotomyRequestForm::RobotomyRequestForm (const RobotomyRequestForm &other)  : AForm ("RobotomyRequestForm", 72, 45)
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