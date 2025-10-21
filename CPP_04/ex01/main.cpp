#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	Animal *a[4] = {new Cat, new Cat, new Dog, new Dog};

	std::cout << "\n-----------------------------------------\n" << std::endl;

	Cat* cat0 = dynamic_cast<Cat*>(a[0]);
	Cat* cat1 = dynamic_cast<Cat*>(a[1]);

	cat0->setIdea(0, "first idea");
	cat0->setIdea(99, "last idea");

	std::cout << "Before assignment:\n";
	std::cout << "cat0: " << cat0->getIdea(0) << " | " << cat0->getIdea(99) << std::endl;
	std::cout << "cat1: " << cat1->getIdea(0) << " | " << cat1->getIdea(99) << std::endl;

	*cat1 = *cat0;

	std::cout << "After assignment:\n";
	std::cout << "cat1: " << cat1->getIdea(0) << " | " << cat1->getIdea(99) << std::endl;

	// test deep copy
	cat0->setIdea(0, "changed idea");
	std::cout << "After modifying cat0:\n";
	std::cout << "cat0: " << cat0->getIdea(0) << std::endl;
	std::cout << "cat1: " << cat1->getIdea(0) << std::endl;

	std::cout << "\n-----------------------------------------\n" << std::endl;

	for (int i = 0; i < 4; i++)
		delete (a[i]);

	return 0;
}