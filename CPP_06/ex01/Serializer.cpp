#include "Serializer.hpp"

Serializer::Serializer ()
{
}

Serializer::Serializer (const Serializer &other)
{
	(void)other;
}

Serializer &Serializer::operator= (const Serializer &obj)
{
	(void)obj;
	return *this;
}

Serializer::~Serializer ()
{
}

