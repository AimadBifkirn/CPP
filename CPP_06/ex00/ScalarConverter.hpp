#pragma once

#include <iostream>
#include <sstream>
#include <limits>

class ScalarConverter
{
	public:

		ScalarConverter ();
		ScalarConverter (const ScalarConverter &other);
		ScalarConverter &operator= (const ScalarConverter &obj);
		~ScalarConverter ();

		static void convert (const std::string &str);
};