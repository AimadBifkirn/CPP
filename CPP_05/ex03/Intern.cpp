#include "Intern.hpp"

Intern::Intern ()
{
}

Intern::Intern (const Intern &other)
{
	(void)other;
}

Intern &Intern::operator= (const Intern &obj)
{
	(void)obj;
	return *this;
}

Intern::~Intern ()
{
}

static AForm *ppf (const std::string &target)
{
	return new PresidentialPardonForm(target);
}

static AForm *rrf (const std::string &target)
{
	return new RobotomyRequestForm(target);
}

static AForm *scf (const std::string &target)
{
	return new ShrubberyCreationForm(target);
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const
{
	std::string forms[] = {"shrubbery creation", "robotomy request", "presidential pardon"};

	AForm *(*functions[3]) (const std::string &) =  {&scf, &rrf, &ppf};

	for (int i = 0; i < 3; i++)
	{
		if (name == forms[i])
			return (*functions[i])(target);
	}
	std::cout << "Intern can not create a form called: " << name << std::endl;
	return NULL;
}