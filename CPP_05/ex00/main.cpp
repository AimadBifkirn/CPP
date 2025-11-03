#include "Bureaucrat.hpp"

int main() {
  try
  {
    Bureaucrat a("b1", 1);
    a.decrement();
    std::cout << a;
    a.increment();
    std::cout << a;
    a.increment();
  }
  catch (std::exception & e)
  {
	  std::cout << e.what() << std::endl;
  }
}