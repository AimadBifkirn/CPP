#include "WrongCat.hpp"

WrongCat::WrongCat ()
{
	this->type = "WrongCat";
	std::cout << "WrongCat: Default constructor called" << std::endl;
}

WrongCat::WrongCat (const WrongCat &other)
{
	*this = other;
	std::cout << "WrongCat: Copy constructor called" << std::endl;
}

WrongCat &WrongCat::operator= (const WrongCat &obj)
{
	if (this != &obj)
	{
		this->type = obj.type;
	}
	std::cout << "WrongCat: Copy assignement operator called" << std::endl;
	return (*this);
}

WrongCat::~WrongCat ()
{
	std::cout << "WrongCat: Destructor called" << std::endl;
}

void WrongCat::makeSound() const
{
	std::cout << "Meaw Meaw!!" << std::endl;
}