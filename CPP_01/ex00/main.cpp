#include "Zombie.hpp"

int	main()
{
	Zombie *z1 = newZombie("zombie1");

	z1->announce();
	delete(z1);
	randomChump("zombie2");
	return (0);
}
