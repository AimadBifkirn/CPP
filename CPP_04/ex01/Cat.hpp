#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain *brain;
	public:
		Cat ();
		Cat (const Cat &other);
		Cat &operator= (const Cat &obj);
		~Cat ();

		void makeSound() const;
		std::string getIdea(int index) const;
		void setIdea(int index, std::string str);
};