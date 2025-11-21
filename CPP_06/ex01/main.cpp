#include "Serializer.hpp"

int main()
{

	Serializer s;
    int* p = new int(65);

	uintptr_t u =  s.serialize(p);
	std::cout << p << std::endl;
	std::cout << *p << std::endl;
	std::cout << u << std::endl;
	
	int *res = (int *)s.deserialize(u);
	std::cout << res << std::endl;
	std::cout << *res << std::endl;
    return 0;
}