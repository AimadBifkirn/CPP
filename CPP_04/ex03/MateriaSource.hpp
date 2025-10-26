#pragma once

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria* materias[4];
	public:
		MateriaSource ();
		MateriaSource (const MateriaSource &other);
		MateriaSource &operator= (const MateriaSource &obj);
		~MateriaSource();

		void learnMateria(AMateria*);
		AMateria* createMateria(std::string const & type);
};