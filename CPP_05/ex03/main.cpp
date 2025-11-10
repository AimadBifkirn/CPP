#include "AForm.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

int main() {
  srand(time(0));
  try
  {
    Bureaucrat b("aimad", 1);
    AForm *form1 = Intern().makeForm("presidential pardon", "target");
    AForm *form2 = Intern().makeForm ("shrubbery creation", "random");
    AForm *form3 = Intern().makeForm ("robotomy request", "tree");

      b.executeForm(*form1);
      b.signForm(*form1);
      b.executeForm(*form1);
      std::cout << "\n----------------------------------\n" << std::endl;
      b.executeForm(*form2);
      b.signForm(*form2);
      b.executeForm(*form2);
      std::cout << "\n----------------------------------\n" << std::endl;
      b.executeForm(*form3);
      b.signForm(*form3);
      b.executeForm(*form3);
  }
  catch (std::exception & e)
  {
	  std::cout << e.what() << std::endl;
  }
}