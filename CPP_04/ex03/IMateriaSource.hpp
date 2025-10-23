#pragma once

#include "AMateria.hpp"

class IMateriaSource
{
	public:

	IMateriaSource ();
	IMateriaSource (const IMateriaSource &other);
	IMateriaSource &operator= (const IMateriaSource &obj);
	virtual ~IMateriaSource();

	virtual void learnMateria(AMateria*) = 0;
	virtual AMateria* createMateria(std::string const & type) = 0;
};