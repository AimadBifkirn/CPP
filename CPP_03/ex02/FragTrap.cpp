#include "FragTrap.hpp"

FragTrap::FragTrap ()
{
	this->HitPoints = 100;
	this->EnergyPoints = 100;
	this->AttackDamage = 30;
	this->Name = "defaut";
	std::cout << "FragTrap: Default constructor called" << std::endl;
}

FragTrap::FragTrap (const FragTrap &other)
{
	*this = other;
	std::cout << "FragTrap: Copy constructor called" << std::endl;
}

FragTrap &FragTrap::operator= (const FragTrap &obj)
{
	if (this != &obj)
	{
		this->HitPoints = obj.HitPoints;
		this->EnergyPoints = obj.EnergyPoints;
		this->AttackDamage = obj.AttackDamage;
		this->Name = obj.Name;
	}
	std::cout << "FragTrap: Copy assignment operator called" << std::endl;
	return (*this);
}

FragTrap::~FragTrap ()
{
	std::cout << "FragTrap: Destructor called" << std::endl;
}

FragTrap::FragTrap (std::string Name)
{
	this->Name = Name;
	this->HitPoints = 100;
	this->EnergyPoints = 100;
	this->AttackDamage = 30;
	std::cout << "FragTrap: Parametrised constructor called" << std::endl;
}

void FragTrap::attack (const std::string& target)
{
	if (this->EnergyPoints > 0 && this->HitPoints > 0)
	{
		this->EnergyPoints--;
		std::cout << "FragTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
	}
	else if (this->EnergyPoints == 0)
		std::cout << "FragTrap " << this->Name << " can't attack because it has no energy points!" << std::endl;
	else
		std::cout << "FragTrap " << this->Name << " can't attack because it has no hit points!" << std::endl;
}

void FragTrap::highFivesGuys()
{
	std::cout << "can we do a high five ?" << std::endl;
}
