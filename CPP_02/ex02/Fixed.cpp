#include "Fixed.hpp"

const int Fixed::fraction = 8;

Fixed::Fixed ()
{
	// std::cout << "Default constructor called" << std::endl;
	this->fp_value = 0;
}

Fixed::Fixed (const Fixed &other)
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed &obj)
{
	// std::cout << "Copy assignment operator called" << std::endl;
	if (this != &obj)
	{
		this->fp_value = obj.getRawBits();
	}
	return (*this);
}

Fixed::~Fixed ()
{
	// std::cout << "Destructor called" << std::endl;
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
	// std::cout << "Int constructor called" << std::endl;
	this->fp_value = value * pow(2, this->fraction);
}

Fixed::Fixed (const float value)
{
	// std::cout << "Float constructor called" << std::endl;
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

Fixed Fixed::operator++ ()
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

Fixed Fixed::operator-- ()
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
	if (a < b)
		return (a);
	return (b);
}

const Fixed &Fixed::min (const Fixed &a, const Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed &max (Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

const Fixed &max (const Fixed &a, const Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}
