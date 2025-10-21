#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	Animal *a[4] = {new Cat, new Cat, new Dog, new Dog};

	std::cout << "\n-----------------------------------------\n" << std::endl;

	dynamic_cast<Cat *>(a[0])->setIdea(0, "first idea");
	dynamic_cast<Cat *>(a[0])->setIdea(99, "last idea");

	std::cout << dynamic_cast<Cat *>(a[0])->getIdea(0) << " | " << dynamic_cast<Cat *>(a[0])->getIdea(99) << std::endl;
	std::cout << dynamic_cast<Cat *>(a[1])->getIdea(0) << " | " << dynamic_cast<Cat *>(a[1])->getIdea(99) << std::endl;

	*(dynamic_cast<Cat *>(a[1])) = *(dynamic_cast<Cat *>(a[0]));

	std::cout << dynamic_cast<Cat *>(a[1])->getIdea(0) << " | " << dynamic_cast<Cat *>(a[1])->getIdea(99) << std::endl;

	std::cout << "\n-----------------------------------------\n" << std::endl;

	for (int i = 0; i < 4; i++)
		delete (a[i]);

	return 0;
}