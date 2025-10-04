#include "Zombie.hpp"
#include <cstdlib>

Zombie*	zombieHorde(int N, std::string name)
{
	Zombie *res = new (std::nothrow) Zombie[N];

	if (!res)
	{
		std::cerr << "new failed\n";
		exit (1);
	}
	for (int i = 0; i < N; i++)
		res[i].setName(name);
	return (res);
}
