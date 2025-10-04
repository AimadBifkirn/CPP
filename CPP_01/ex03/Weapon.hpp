#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <iostream>

class Weapon
{
	private:
		std::string	type;
	public:
		const std::string& getType();
		void	setType(std::string new_type);
		Weapon(std::string	new_type);
};

#endif