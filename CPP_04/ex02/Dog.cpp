#include "Dog.hpp"

Dog::Dog ()
{
	this->brain = new Brain();
	this->type = "Dog";
	std::cout << "Dog: Default constructor called" << std::endl;
}

Dog::Dog (const Dog &other)
{
	this->brain = new Brain();
	*this = other;
	std::cout << "Dog: Copy constructor called" << std::endl;
}

Dog &Dog::operator= (const Dog &obj)
{
	if (this != &obj)
	{
		this->type = obj.type;
		*(this->brain) = *(obj.brain);
	}
	std::cout << "Dog: Copy assignement operator called" << std::endl;
	return (*this);
}

Dog::~Dog ()
{
	std::cout << "Dog: Destructor called" << std::endl;
	delete (this->brain);
}

void Dog::makeSound() const
{
	std::cout << "Bark Bark!!" << std::endl;
}

std::string Dog::getIdea(int index) const
{
	if (index >= 0 && index < 100)
	{
		return (this->brain->ideas[index]);
	}
	return "";
}

void Dog::setIdea(int index, std::string str)
{
	if (index >= 0 && index < 100)
	{
		this->brain->ideas[index] = str;
	}
}