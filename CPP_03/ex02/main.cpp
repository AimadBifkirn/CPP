#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main ()
{
	FragTrap s("derived");
	s.attack("l3do");
	s.takeDamage(90);
	s.beRepaired(10);
	s.highFivesGuys();
}