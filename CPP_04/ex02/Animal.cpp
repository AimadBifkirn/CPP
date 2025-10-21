#include "Animal.hpp"

Animal::Animal () : type("Animal")
{
	std::cout << "Animal: Default constructor called" << std::endl;
}

Animal::Animal (const Animal &other)
{
	*this = other;
	std::cout << "Animal: Copy constructor called" << std::endl;
}

Animal &Animal::operator= (const Animal &obj)
{
	if (this != &obj)
	{
		this->type = obj.type;
	}
	std::cout << "Animal: Copy assignement operator called" << std::endl;
	return (*this);
}

Animal::~Animal ()
{
	std::cout << "Animal: Destructor called" << std::endl;
}

const std::string &Animal::getType(void) const
{
	return (this->type);
}

void Animal::makeSound() const
{
	std::cout << "Animal sound!!" << std::endl;
}