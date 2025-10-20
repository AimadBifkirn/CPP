#include "Dog.hpp"

Dog::Dog ()
{
	this->type = "Dog";
	std::cout << "Dog: Default constructor called" << std::endl;
}

Dog::Dog (const Dog &other)
{
	*this = other;
	std::cout << "Dog: Copy constructor called" << std::endl;
}

Dog &Dog::operator= (const Dog &obj)
{
	if (this != &obj)
	{
		this->type = obj.type;
	}
	std::cout << "Dog: Copy assignement operator called" << std::endl;
	return (*this);
}

Dog::~Dog ()
{
	std::cout << "Dog: Destructor called" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Bark Bark!!" << std::endl;
}