#include "Cat.hpp"

Cat::Cat ()
{
	this->brain = new Brain();
	this->type = "Cat";
	std::cout << "Cat: Default constructor called" << std::endl;
}

Cat::Cat (const Cat &other)
{
	this->brain = new Brain();
	*this = other;
	std::cout << "Cat: Copy constructor called" << std::endl;
}

Cat &Cat::operator= (const Cat &obj)
{
	if (this != &obj)
	{
		this->Animal::operator=(obj);
		*(this->brain) = *(obj.brain);
	}
	std::cout << "Cat: Copy assignement operator called" << std::endl;
	return (*this);
}

Cat::~Cat ()
{
	std::cout << "Cat: Destructor called" << std::endl;
	delete (this->brain);
}

void Cat::makeSound() const
{
	std::cout << "Meaw Meaw!!" << std::endl;
}

std::string Cat::getIdea(int index) const
{
	if (index >= 0 && index < 100)
	{
		return (this->brain->ideas[index]);
	}
	return "";
}

void Cat::setIdea(int index, std::string str)
{
	if (index >= 0 && index < 100)
	{
		this->brain->ideas[index] = str;
	}
}