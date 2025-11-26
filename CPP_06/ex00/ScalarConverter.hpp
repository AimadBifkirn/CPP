#pragma once

#include <iostream>
#include <sstream>
#include <limits>
#include <math.h>

class ScalarConverter
{
	public:

		ScalarConverter ();
		ScalarConverter (const ScalarConverter &other);
		ScalarConverter &operator= (const ScalarConverter &obj);
		~ScalarConverter ();

		static void convert (std::string str);
};