#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie
{
	private:
			std::string name;
	public:
			void	announce(void);
			Zombie(std::string n_name);
			~Zombie(void);
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif