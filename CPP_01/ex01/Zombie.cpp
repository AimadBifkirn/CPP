#include "Zombie.hpp"

void	Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string n_name)
{
	name = n_name;
}

Zombie::~Zombie(void)
{
	std::cout << "zombie -> " << this->name << ": died" << std::endl;
}
