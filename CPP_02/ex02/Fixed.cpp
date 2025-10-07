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
	// std::cout << "getRawBits member function called" << std::endl;
	return (this->fp_value);
}

void	Fixed::setRawBits(int const raw)
{
	// std::cout << "SetRawBits member function called" << std::endl;
	this->fp_value = raw;
}

Fixed::Fixed (const int value)
{
	std::cout << "Int constructor called" << std::endl;
	this->fp_value = value * pow(2, this->fraction);
}

Fixed::Fixed (const float value)
{
	std::cout << "Float constructor called" << std::endl;
	this->fp_value = roundf(value * pow(2, this->fraction));
}

int	Fixed::toInt(void) const
{
	return (this->fp_value / pow(2, this->fraction));
}

float Fixed::toFloat (void) const
{
	return (this->fp_value / (float)pow(2, this->fraction));
}

std::ostream &operator<< (std::ostream &out, const Fixed &obj)
{
	out << obj.toFloat();
	return (out);
}
