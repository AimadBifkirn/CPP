#include "HumanA.hpp"

void	HumanA::attack(void)
{
	std::cout  << this->name << " attacks with their " << this->slah.getType() << std::endl;
}

HumanA::HumanA(std::string new_name, Weapon &new_wepon)
: slah(new_wepon), name(new_name)
{
}
