#pragma once

#include <iostream>
#include "ICharacter.hpp"

class AMateria
{
	protected:
		std::string type;
	public:

		AMateria ();
		AMateria (const AMateria &other);
		AMateria &operator= (const AMateria &obj);
		virtual ~AMateria ();
		
		AMateria(std::string const & type);
		std::string const & getType() const; //Returns the materia type

		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target) = 0;
};