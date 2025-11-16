#pragma once

#include <iostream>

class ScalarConverter
{
	public:

		ScalarConverter ();
		ScalarConverter (const ScalarConverter &other);
		ScalarConverter &operator= (const ScalarConverter &obj);
		~ScalarConverter ();

		static void convert (const std::string &str);
};