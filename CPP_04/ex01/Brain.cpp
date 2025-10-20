#include "Brain.hpp"

Brain::Brain ()
{
	std::cout << "Brain: Default constructor called" << std::endl;
}

Brain::Brain (const Brain &other)
{
	*this = other;
	std::cout << "Brain: Copy constructor called" << std::endl;
}

Brain &Brain::operator= (const Brain &obj)
{
	if (this != &obj)
	{
		// i have to coppy the ideas inside brain (deep copy)
	}
	std::cout << "Brain: Copy assignement operator called" << std::endl;
	return (*this);
}

Brain::~Brain ()
{
	std::cout << "Brain: Destructor called" << std::endl;
}