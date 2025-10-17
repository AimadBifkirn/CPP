#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
	this->EnergyPoints = 10;
	this->HitPoints = 10;
	this->AttackDamage = 0;
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap (const ClapTrap &other)
{
	*this = other;
	std::cout << "Copy constructor called" << std::endl;
}

ClapTrap  &ClapTrap::operator= (const ClapTrap &obj)
{
	if (this != &obj)
	{
		this->Name = obj.Name;
		this->EnergyPoints = obj.EnergyPoints;
		this->HitPoints = obj.HitPoints;
		this->AttackDamage = obj.AttackDamage;
	}
	std::cout << "Copy assignment operator called" << std::endl;
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string &Name)
{
	this->Name = Name;
	std::cout << "Parametrised constructor called" << std::endl;
}

