#pragma once

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
	public:
		WrongCat ();
		WrongCat (const WrongCat &other);
		WrongCat &operator= (const WrongCat &obj);
		~WrongCat ();
		void makeSound() const;
};