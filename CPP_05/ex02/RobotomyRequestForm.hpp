#pragma once

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		std::string target;
	public:
		RobotomyRequestForm ();
		RobotomyRequestForm (const RobotomyRequestForm &other);
		RobotomyRequestForm &operator= (const RobotomyRequestForm &obj);
		~RobotomyRequestForm ();

		RobotomyRequestForm (const std::string &target);
		void executeForm () const;
};