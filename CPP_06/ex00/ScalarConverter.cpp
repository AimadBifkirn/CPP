#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter ()
{
}

ScalarConverter::ScalarConverter (const ScalarConverter &other)
{
}

ScalarConverter &ScalarConverter::operator= (const ScalarConverter &obj)
{
	return *this;
}

ScalarConverter::~ScalarConverter ()
{
}

static bool is_integer (const std::string &str)
{
	

	return false;
}

void ScalarConverter::convert (const std::string &str)
{
	if (!is_integer(str) && !is_float(str) && !is_double(str) && !is_char(str) && !is_special(str))
	{
		std::cout << "char: impossible\n int: possible\n float: impossible\n double: impossible" << std::endl;
		return ;
	}

	if (is_integer())
		return (print_integer());
	if (str.length() <= 1)
		return (print_char());
	if (is_float())
		return (print_float());
	if (is_double())
		return (print_double());
}