#pragma once

#include "ICharacter.hpp"

class Character : public ICharacter
{
	private:
		std::string name;
		AMateria *slot[4];
		AMateria *deleted[100];
		int			d_idx;
	public:

		Character ();
		Character (const Character &other);
		Character &operator= (const Character &obj);
		~Character ();

		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
		Character(std::string const &name);
};