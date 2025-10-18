#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
	this->EnergyPoints = 50;
	this->HitPoints = 100;
	this->AttackDamage = 20;
	this->Name = "default";
	std::cout << "ClapTrap: Default constructor called" << std::endl;
}

ClapTrap::ClapTrap (const ClapTrap &other)
{
	*this = other;
	std::cout << "ClapTrap: Copy constructor called" << std::endl;
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
	std::cout << "ClapTrap: Copy assignment operator called" << std::endl;
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap: Destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string Name)
{
	this->Name = Name;
	this->EnergyPoints = 50;
	this->HitPoints = 100;
	this->AttackDamage = 20;
	std::cout << "ClapTrap: Parametrised constructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (this->EnergyPoints > 0 && this->HitPoints > 0)
	{
		this->EnergyPoints--;
		std::cout << "ClapTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
	}
	else if (this->EnergyPoints == 0)
		std::cout << "ClapTrap " << this->Name << " can't attack because it has no energy points!" << std::endl;
	else
		std::cout << "ClapTrap " << this->Name << " can't attack because it has no hit points!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->HitPoints > amount)
	{
		this->HitPoints -= amount;
		std::cout << "ClapTrap " << this->Name << " was attacked and lost " << amount << " hit points, it has now " << this->HitPoints << " hit points!" << std::endl;
	}
	else if (this->HitPoints > 0)
	{
		std::cout << "ClapTrap " << this->Name << " was attacked and lost " << this->HitPoints << " of hit points, it has now 0 hit points!" << std::endl;
		this->HitPoints = 0;
	}
	else
		std::cout << "ClapTrap " << this->Name << " is dead!!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->HitPoints > 0 && this->EnergyPoints > 0)
	{
		this->EnergyPoints--;
		this->HitPoints += amount;
		std::cout << "ClapTrap " << this->Name << " repaired itself with " << amount << " hit points, it has now " << this->HitPoints << " hit points!" << std::endl;
	}
	else if (this->EnergyPoints == 0)
		std::cout << "ClapTrap " << this->Name << " can't be repaired because it has no energy points!" << std::endl;
	else if (this->HitPoints == 0)
		std::cout << "ClapTrap " << this->Name << " can't be repaired because it has no hit points!" << std::endl;
}
