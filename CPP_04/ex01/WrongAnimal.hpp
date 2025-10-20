#pragma once

#include <iostream>

class WrongAnimal
{
	protected:
		std::string type;
	public:
		WrongAnimal ();
		WrongAnimal (const WrongAnimal &other);
		WrongAnimal &operator= (const WrongAnimal &obj);
		~WrongAnimal ();

		const std::string &getType(void) const;
		void makeSound() const;
};