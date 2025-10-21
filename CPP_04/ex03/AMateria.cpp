#include "AMateria.hpp"

AMateria::AMateria () : type("AMateria")
{
}

AMateria::AMateria (const AMateria &other)
{
	*this = other;
}

AMateria &AMateria::operator= (const AMateria &obj)
{
	if (this != &obj)
	{
		this->type = obj.type;
	}
	return (*this);
}

AMateria::~AMateria ()
{
}

AMateria::AMateria(std::string const & type)
{
	this->type = type;
}

std::string const & AMateria::getType() const
{
	return (this->type);
}