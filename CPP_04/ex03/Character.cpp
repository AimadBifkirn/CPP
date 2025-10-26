#include "Character.hpp"
#include "AMateria.hpp"

Character::Character () : d_idx (0)
{
	this->name = "Character";

	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
	for (int i = 0; i < 100; i++)
		this->deleted[i] = NULL;
}

Character::Character (const Character &other)
{
	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
	for (int i = 0; i < 100; i++)
		this->deleted[i] = NULL;
	*this = other;
}

Character &Character::operator= (const Character &obj)
{
	if (this != &obj)
	{ // deep copy needed
		for (int i = 0; i < 4; i++)
		{
			delete (this->slot[i]);
			if (obj.slot[i])
				this->slot[i] = obj.slot[i]->clone();
			else
				this->slot[i] = NULL;
		}
		this->d_idx = 0;
		this->name = obj.name;
	}
	return (*this);
}

Character::~Character ()
{
	for (int i = 0; i < 4; i++)
		delete this->slot[i];
	for (int i = 0; i < 100; i++)
		delete this->deleted[i];
}

Character::Character(std::string const &name)
{
	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
	for (int i = 0; i < 100; i++)
		this->deleted[i] = NULL;
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
		if (this->slot[i] == m)
		{
			std::cout << "Already stored this materia!" << std::endl;
			return ;
		}
		if (this->slot[i] == NULL)
		{
			this->slot[i] = m;
			return ;
		}
	}
	delete m;
}

void Character::unequip(int idx)
{
	if (this->deleted[99]) {
		std::cout << "can't unequip, the buffer is full!" << std::endl;
		return;
	}
	for (int i = 0; i < 100 ; i++)
	{
		if (this->slot[idx] == this->deleted[i])
			break;
		if (this->deleted[i] == NULL)
		{
			this->deleted[i] = this->slot[idx];
			break ;
		}
	}
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