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
	if (str.empthy())
		return false;

	size_t pos = 0;

	if (str[0] == '+' || str[0] == '-')
	{
		if (str.length() == 1)
			return false;
		pos++;
	}

	for (i; str[i]; i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

static bool is_char (const std::string &str)
{
	return (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]));
}


void ScalarConverter::convert (const std::string &str)
{
	if (!is_char(str) && !is_float(str) && !is_double(str) && !is_integer(str) && !is_special(str))
	{
		std::cout << "char: impossible\n int: possible\n float: impossible\n double: impossible" << std::endl;
		return ;
	}

	if (str.length() <= 1)
		return (print_char());
	if (is_integer())
		return (print_integer());
	if (is_float())
		return (print_float());
	if (is_double())
		return (print_double());
}