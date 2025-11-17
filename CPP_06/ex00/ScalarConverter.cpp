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
	if (str.empty())
		return false;

	int i = 0;

	if (str[0] == '+' || str[0] == '-')
	{
		if (str.length() == 1)
			return false;
		i++;
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
	return (str.length() == 1 && str.empty() && !std::isdigit(str[0]));
}

static bool is_float (const std::string &str)
{
	if (str.empty())
		return false;
	
	int i = 0;

	if (str[0] == '+' || str[0] == '-')
	{
		if (str.length() == 1)
			return false;
		i++;
	}
	for (i; str[i]; i++)
	{
		if (i == 1 && !std::isdigit(str[i]))
			return false;
		else if 
	}
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