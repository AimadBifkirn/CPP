#include "Form.hpp"
#include "Bureaucrat.hpp"

int main() {
  try
  {
    Bureaucrat a("b1", 20);
    Form f("tawri9t", 20, 10);
    std::cout << f << std::endl;
    a.signForm(f);
    std::cout << f << std::endl;
  }
  catch (std::exception & e)
  {
	  std::cout << e.what() << std::endl;
  }
}