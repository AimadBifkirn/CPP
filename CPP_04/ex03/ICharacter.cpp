#include "ICharacter.hpp"

ICharacter::ICharacter ()
{
}

ICharacter::ICharacter (const ICharacter &other)
{
	*this = other;
}

ICharacter &ICharacter::operator= (const ICharacter &obj)
{
	(void)obj;
	return (*this);
}

ICharacter::~ICharacter ()
{
}
