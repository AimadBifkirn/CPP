#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	public:
		FragTrap ();
		FragTrap (const FragTrap &other);
		FragTrap &operator= (const FragTrap &obj);
		~FragTrap ();

		FragTrap (std::string Name);
		void attack(const std::string& target);
		void highFivesGuys(void);
};

#endif