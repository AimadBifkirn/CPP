#include "IMateriaSource.hpp"

IMateriaSource::IMateriaSource ()
{
}

IMateriaSource::IMateriaSource (const IMateriaSource &other)
{
	*this = other;
}

IMateriaSource &IMateriaSource::operator= (const IMateriaSource &obj)
{
	(void)obj;
	return (*this);
}

IMateriaSource::~IMateriaSource ()
{
}