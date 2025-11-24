#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base * generate(void)
{
	int r = rand() % 3;
	if (r == 0)
		return new A;
	else if (r == 1)
		return new B;
	else
		return new C;
}

void identify(Base* p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "The object type is: A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "The object type is: B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "The object type is: C" << std::endl;
	else
		std::cout << "Unknown type !!" << std::endl;
}

void identify(Base& p)
{
	try
	{
		A a = dynamic_cast<A &>(p);
		std::cout << "The type of the object referenced by is: A" << std::endl;
		return ;
	}
	catch(const std::exception& e)
	{
	}

	try
	{
		B b = dynamic_cast<B &>(p);
		std::cout << "The type of the object referenced by is: B" << std::endl;
		return ;
	}
	catch(const std::exception& e)
	{
	}
	

	try
	{
		C c = dynamic_cast<C &>(p);
		std::cout << "The type of the object referenced by is: C" << std::endl;
		return ;
	}
	catch(const std::exception& e)
	{
	}

	std::cout << "Unknown type !!" << std::endl;
}

int main ()
{
	srand(time(0));

	Base* instance = generate();
	
    std::cout << "--------------------" << std::endl;
    identify(instance);

    std::cout << "--------------------" << std::endl;
    identify(*instance);

    std::cout << "--------------------" << std::endl;
    identify(NULL);

    std::cout << "--------------------" << std::endl;
    identify(NULL);

    delete instance;
	return (0);
}