#pragma once

#include "IMateriaSource.hpp"

class MateriaSource
{
	private:
		AMateria* materias[4];
	public:
		MateriaSource ();
		MateriaSource (const MateriaSource &other);
		MateriaSource &operator= (const MateriaSource &obj);
		~MateriaSource();
};