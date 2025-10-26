#include "Ice.hpp"

Ice::Ice ()
{
	this->type = "ice";
}

Ice::Ice (const Ice &other)
{
	*this = other;
}

Ice &Ice::operator= (const Ice &obj)
{
	(void)obj;
	return (*this);
}

Ice::~Ice ()
{
}

Ice* Ice::clone() const
{
	return (new Ice);
}

void Ice::use(ICharacter& target)
{
	std::cout <<  "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}