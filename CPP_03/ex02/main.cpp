#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main ()
{
	FragTrap s("derived");
	s.attack("l3do");
	s.beRepaired(10);
	s.takeDamage(100);
	s.highFivesGuys();
}