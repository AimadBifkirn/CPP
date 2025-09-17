#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
	private:
		Weapon		*slah;
		std::string	name;
	public:
		HumanB(std::string new_name);
		void	attack();
		void	setWeapon(Weapon &new_weapon);
};

#endif