#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

int main() {
  srand(time(0));
  try
  {
      PresidentialPardonForm form1("target");
      ShrubberyCreationForm form2 ("random");
      RobotomyRequestForm form3 ("tree");
      Bureaucrat b("aimad", 50);

      std::cout << "\n----------------------------------" << std::endl;
      b.executeForm(form1);
      b.signForm(form1);
      b.executeForm(form1);
      std::cout << "\n----------------------------------" << std::endl;
      b.executeForm(form2);
      b.signForm(form2);
      b.executeForm(form2);
      std::cout << "\n----------------------------------" << std::endl;
      b.executeForm(form3);
      b.signForm(form3);
      b.executeForm(form3);
      b.executeForm(form3);
      b.executeForm(form3);
  }
  catch (std::exception & e)
  {
	  std::cout << e.what() << std::endl;
  }
}