#include "ScavTrap.hpp"

ScavTrap::ScavTrap ()
{
	std::cout << "ScavTrap: Default constructor called" << std::endl;
}

ScavTrap::ScavTrap (const ScavTrap &other)
{
	*this = other;
	std::cout << "ScavTrap: Copy constructor called" << std::endl;
}

ScavTrap &ScavTrap::operator= (const ScavTrap &obj)
{
		this->ClapTrap::operator=(obj);
		std::cout << "ScavTrap: Copy assignment operator called" << std::endl;
		return (*this);
}

ScavTrap::~ScavTrap ()
{
	std::cout << "ScavTrap: Destructor called" << std::endl;
}

ScavTrap::ScavTrap (std::string Name)
{
	this->Name = Name;
	std::cout << "ScavTrap: Parametrised constructor called" << std::endl;
}

void ScavTrap::attack (const std::string& target)
{
	if (this->EnergyPoints > 0 && this->HitPoints > 0)
	{
		this->EnergyPoints--;
		std::cout << "ScavTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
	}
	else if (this->EnergyPoints == 0)
		std::cout << "ScavTrap " << this->Name << " can't attack because it has no energy points!" << std::endl;
	else
		std::cout << "ScavTrap " << this->Name << " can't attack because it has no hit points!" << std::endl;
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap is now in Gate keeper mode!" << std::endl;
}
