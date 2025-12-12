#include "Serializer.hpp"

int main()
{
    Data d = {1337, 'A'};

	uintptr_t u =  Serializer::serialize(&d);
	std::cout << &d << std::endl;
	std::cout << "int i = " << d.i << ", char c = " << d.c << std::endl;
	std::cout << u << std::endl;
	
	Data *res = Serializer::deserialize(u);
	std::cout << res << std::endl;
	std::cout << "int i = " << res->i << ", char c = " << res->c << std::endl;
    return 0;
}