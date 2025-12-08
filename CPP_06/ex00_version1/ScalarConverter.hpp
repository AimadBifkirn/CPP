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
	public:
		ScalarConverter &operator= (const ScalarConverter &obj);
		~ScalarConverter ();

		static void convert (std::string str);
};