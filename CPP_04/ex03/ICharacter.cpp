#include "ICharacter.hpp"

ICharacter::ICharacter () : name("default ICharacter")
{
}

ICharacter::ICharacter (const ICharacter &other)
{
	*this = other;
}

ICharacter &ICharacter::operator= (const ICharacter &obj)
{
	if (this != &obj)
	{
		this->name = obj.name;
	}
	return (*this);
}

ICharacter::~ICharacter ()
{
}

ICharacter::ICharacter(std::string const &name)
{
	this->name = name;
}

std::string const & ICharacter::getName() const
{
	return (this->name);
}

void ICharacter::use(int idx, ICharacter& target)
{
	
}