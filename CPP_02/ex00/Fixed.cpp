#include "Fixed.hpp"

const int Fixed::fraction = 8;

Fixed::Fixed ()
{
	std::cout << "Default constructor called" << std::endl;
	this->fp_value = 0;
}

Fixed::Fixed (const Fixed &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed &obj)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->fp_value = obj.getRawBits();
	}
	return (*this);
}

Fixed::~Fixed ()
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->fp_value);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "SetRawBits member function called" << std::endl;
	this->fp_value = raw;
}
