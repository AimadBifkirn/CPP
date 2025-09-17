#include "HumanB.hpp"

void	HumanB::attack(void)
{
	if (!slah)
		std::cout  << this->name << " has no weapon!" << std::endl;
	else
		std::cout  << this->name << " attacks with their " << this->slah->getType() << std::endl;
}

HumanB::HumanB(std::string new_name)
{
	this->name = new_name;
	this->slah = NULL;
}
void	HumanB::setWeapon(Weapon &new_weapon)
{
	this->slah = &new_weapon;
}
