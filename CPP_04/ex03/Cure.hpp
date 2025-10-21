#pragma once

#include "AMateria.hpp"

class Cure : public AMateria
{
	public:
		Cure ();
		Cure (const Cure &other);
		Cure &operator= (const Cure &obj);
		~Cure ();

		Cure* clone() const;
		void use(ICharacter& target);
};