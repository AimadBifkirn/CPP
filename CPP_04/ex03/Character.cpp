#include "Character.hpp"
#include "AMateria.hpp"

Character::Character () : d_idx (0)
{
	this->name = "Character";

	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
}

Character::Character (const Character &other)
{
	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
	*this = other;
}

Character &Character::operator= (const Character &obj)
{
	if (this != &obj)
	{ // deep copy needed
		this->d_idx = 0;
		this->name = obj.name;
	}
	return (*this);
}

Character::~Character ()
{
}

Character::Character(std::string const &name)
{
	this->name = name;
}

std::string const & Character::getName() const
{
	return (this->name);
}

void Character::equip(AMateria* m)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->slot[i] == NULL)
			this->slot[i] = m;
	}
}

void Character::unequip(int idx)
{


	this->slot[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx > 3)
	{
		std::cerr << "The index must be between 0 and 3!" << std::endl;
		return ;
	}
	if (this->slot[idx] != NULL)
		this->slot[idx]->use(target);
	else
		std::cerr << "No materia at the given index!" << std::endl;
}