#pragma once

#include <iostream>

class Animal
{
	protected:
		std::string type;
	public:
		Animal ();
		Animal (const Animal &other);
		Animal &operator= (const Animal &obj);
		virtual ~Animal ();

		const std::string &getType(void) const;
		virtual void makeSound() const = 0;
};