#include "Cure.hpp"

Cure::Cure ()
{
	this->type = "cure";
}

Cure::Cure (const Cure &other)
{
	*this = other;
}

Cure &Cure::operator= (const Cure &obj)
{
	(void)obj;
	return (*this);
}

Cure::~Cure ()
{
}

Cure* Cure::clone() const
{
	return (new Cure);
}

void Cure::use(ICharacter& target)
{
	std::cout <<  "* heals " << target.getName() << "’s wounds *" << std::endl;
}