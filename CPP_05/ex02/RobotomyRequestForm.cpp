#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm () : AForm ("RobotomyRequestForm", 72, 45), target("default")
{
}

RobotomyRequestForm::RobotomyRequestForm (const RobotomyRequestForm &other)  : AForm ("RobotomyRequestForm", 72, 45)
{
	*this = other;
}

RobotomyRequestForm &RobotomyRequestForm::operator= (const RobotomyRequestForm &obj)
{
	if (this != &obj)
	{
		RobotomyRequestForm::AForm::operator=(obj);
		this->target = obj.target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm ()
{
}

RobotomyRequestForm::RobotomyRequestForm (const std::string &target) : AForm ("RobotomyRequestForm", 72, 45), target(target)
{
}

void RobotomyRequestForm::executeForm () const
{
	std::cout << "Br Br Brgzzzz" << std::endl;
	if (rand() % 2)
		std::cout << this->target << " has been robotomized successfully" << std::endl;
	else
		std::cout << "The " << this->target << " robotomy failed" << std::endl;
}