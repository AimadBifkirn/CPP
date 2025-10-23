#include "MateriaSource.hpp"

MateriaSource::MateriaSource ()
{
	for (int i = 0; i < 4; i++)
		this->materias[i] = NULL;
}

MateriaSource::MateriaSource (const MateriaSource &other)
{
	for (int i = 0; i < 4; i++)
		this->materias[i] = NULL;
	*this = other;
}

MateriaSource &MateriaSource::operator= (const MateriaSource &obj)
{
	for (int i = 0; i < 4; i++)
	{
		delete this->materias[i];
		this->materias[i] = obj.materias[i]->clone();
	}
	return (*this);
}

MateriaSource::~MateriaSource ()
{
}