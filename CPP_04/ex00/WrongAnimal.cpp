#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal () : type("WrongAnimal")
{
	std::cout << "WrongAnimal: Default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal (const WrongAnimal &other)
{
	*this = other;
	std::cout << "WrongAnimal: Copy constructor called" << std::endl;
}

WrongAnimal &WrongAnimal::operator= (const WrongAnimal &obj)
{
	if (this != &obj)
	{
		this->type = obj.type;
	}
	std::cout << "WrongAnimal: Copy assignement operator called" << std::endl;
	return (*this);
}

WrongAnimal::~WrongAnimal ()
{
	std::cout << "WrongAnimal: Destructor called" << std::endl;
}

const std::string &WrongAnimal::getType(void) const
{
	return (this->type);
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal sound!!" << std::endl;
}