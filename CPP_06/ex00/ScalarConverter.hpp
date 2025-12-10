#pragma once

#include <iostream>
#include <sstream>
#include <limits>
#include <math.h>

class ScalarConverter
{
	private:
		ScalarConverter ();
		ScalarConverter (const ScalarConverter &other);
		ScalarConverter &operator= (const ScalarConverter &obj);
		~ScalarConverter ();
	public:

		static void convert (std::string str);
};