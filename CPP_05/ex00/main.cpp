#include <iostream>
#include <stdexcept>
#include <exception> 

class errorGradeToLow: public std::exception {
	public:
		const char* what() const throw() {
			return "name.c_str()";
		}
};

int main() {
  try
  {
     throw errorGradeToLow();
  }
  catch (std::exception & e)
  {
	std::cout << e.what();
  }
}