#include "Cat.hpp"

Cat::Cat ()
{
	this->type = "Cat";
	std::cout << "Cat: Default constructor called" << std::endl;
}

Cat::Cat (const Cat &other)
{
	*this = other;
	std::cout << "Cat: Copy constructor called" << std::endl;
}

Cat &Cat::operator= (const Cat &obj)
{
	if (this != &obj)
	{
		this->type = obj.type;
	}
	std::cout << "Cat: Copy assignement operator called" << std::endl;
	return (*this);
}

Cat::~Cat ()
{
	std::cout << "Cat: Destructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Meaw Meaw!!" << std::endl;
}