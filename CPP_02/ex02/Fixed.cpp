#include "Fixed.hpp"

const int Fixed::fraction = 8;

Fixed::Fixed ()
{
	this->fp_value = 0;
}

Fixed::Fixed (const Fixed &other)
{
	*this = other;
}

Fixed& Fixed::operator=(const Fixed &obj)
{
	if (this != &obj)
	{
		this->fp_value = obj.getRawBits();
	}
	return (*this);
}

Fixed::~Fixed ()
{
}

int Fixed::getRawBits(void) const
{
	return (this->fp_value);
}

void	Fixed::setRawBits(int const raw)
{
	this->fp_value = raw;
}

Fixed::Fixed (const int value)
{
	this->fp_value = value * (1 << this->fraction);
}

Fixed::Fixed (const float value)
{
	this->fp_value = roundf(value * (1 << this->fraction));
}

int	Fixed::toInt(void) const
{
	return (this->fp_value / (1 << this->fraction));
}

float Fixed::toFloat (void) const
{
	return (this->fp_value / (float)(1 << this->fraction));
}

std::ostream &operator<< (std::ostream &out, const Fixed &obj)
{
	out << obj.toFloat();
	return (out);
}

bool Fixed::operator> (const Fixed &obj)  const
{
	return (this->fp_value > obj.fp_value);
}

bool Fixed::operator< (const Fixed &obj) const
{
	return (this->fp_value < obj.fp_value);
}

bool Fixed::operator== (const Fixed &obj) const
{
	return (this->fp_value == obj.fp_value);
}

bool Fixed::operator>= (const Fixed &obj) const
{
	return (this->fp_value >= obj.fp_value);
}

bool Fixed::operator<= (const Fixed &obj) const
{
	return (this->fp_value <= obj.fp_value);
}

bool Fixed::operator!= (const Fixed &obj) const
{
	return (this->fp_value != obj.fp_value);
}

Fixed Fixed::operator+ (const Fixed &obj)
{
	return (Fixed (this->toFloat() + obj.toFloat()));
}

Fixed Fixed::operator- (const Fixed &obj)
{
	return (Fixed (this->toFloat() - obj.toFloat()));
}

Fixed Fixed::operator* (const Fixed &obj)
{
	return (Fixed (this->toFloat() * obj.toFloat()));
}

Fixed Fixed::operator/ (const Fixed &obj)
{
	return (Fixed (this->toFloat() / obj.toFloat()));
}

Fixed &Fixed::operator++ ()
{
	this->fp_value++;
	return (*this);
}

Fixed Fixed::operator++ (int)
{
	Fixed res(*this);
	this->fp_value++;
	return (res);
}

Fixed &Fixed::operator-- ()
{
	this->fp_value--;
	return (*this);
}

Fixed Fixed::operator-- (int)
{
	Fixed res(*this);
	this->fp_value--;
	return (res);
}

Fixed &min (Fixed &a, Fixed &b)
{
	return (a < b ? a : b);
}

const Fixed &Fixed::min (const Fixed &a, const Fixed &b)
{
	return (a < b ? a : b);
}

Fixed &Fixed::max (Fixed &a, Fixed &b)
{
	return (a > b ? a : b);
}

const Fixed &Fixed::max (const Fixed &a, const Fixed &b)
{
	return (a > b ? a : b);
}
