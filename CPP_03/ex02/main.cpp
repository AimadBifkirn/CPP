#include "ScavTrap.hpp"

int main ()
{
	ScavTrap s("derived");
	s.attack("l3do");
	s.beRepaired(10);
	s.takeDamage(100);
	s.guardGate();
}