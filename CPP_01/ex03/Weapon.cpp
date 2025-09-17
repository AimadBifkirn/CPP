#include "Weapon.hpp"

std::string Weapon::getType(void)
{
	return (this->type);
}

void	Weapon::setType(std::string new_type)
{
	this->type = new_type;
}

Weapon::Weapon(std::string new_type)
{
	this->type = new_type;
}
