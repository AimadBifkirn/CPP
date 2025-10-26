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
		if (obj.materias[i])
			this->materias[i] = obj.materias[i]->clone();
		else
			this->materias[i] = NULL;
	}
	return (*this);
}

MateriaSource::~MateriaSource ()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->materias[i])
			delete this->materias[i];
	}
}

void MateriaSource::learnMateria(AMateria* mtobj)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->materias[i] == mtobj)
		{
			std::cout << "Already learned this materia!" << std::endl;
			return ;
		}
		if (this->materias[i] == NULL)
		{
			this->materias[i] = mtobj;
			return ;
		}
	}
	delete (mtobj);
	std::cout << "Can't store more then 4 materias, the materia you passed is deleted!" << std::endl;
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->materias[i] != NULL && type == this->materias[i]->getType())
		{
			return (this->materias[i]->clone());
		}
	}
	return (0);
}