#include "Zombie.hpp"

int main()
{
	int num = 3;
	Zombie *n = zombieHorde(num, "hamid");
	for (int i = 0; i < num; i++)
		n[i].announce();
	delete[] n;
	return (0);
}
