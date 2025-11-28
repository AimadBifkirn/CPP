#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter ()
{
}

ScalarConverter::ScalarConverter (const ScalarConverter &other)
{
	(void)other;
}

ScalarConverter &ScalarConverter::operator= (const ScalarConverter &obj)
{
	(void)obj;
	return *this;
}

ScalarConverter::~ScalarConverter ()
{
}

static bool is_double(const std::string &str)
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

	int x = 0;
	int y = 0;
	int stop = str.length();
	if (str.length() != 1 && str[str.length() - 1] == 'f')
		stop = str.length() - 1;

	for (int idx = i; idx < stop; idx++)
	{
		if (!y && !std::isdigit(str[idx]))
			return false;
		else if (str[idx] == '.' && !x)
			x = 1;
		else if (!std::isdigit(str[idx]))
			return false;
		y = 1;
	}
	if (str[stop - 1] == '.')
		return false;

	return true;
}

static bool is_special (const std::string &str)
{
	return (str == "-inff" || str == "+inff" || str == "nanf" || str == "-inf" || str == "+inf" || str == "nan");
}

static void printImpossible ()
{
	std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
}

static void print_double(const std::string &str)
{
	std::istringstream toConvert(str);
	double d;

	toConvert >> d;
	if (toConvert.fail())
		return printImpossible();
	char c = static_cast<char>(d);
	int i = static_cast<int>(d);
	float f = static_cast<float>(d);

	if (d < 0 || d > std::numeric_limits<char>::max())
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: " << (std::isprint(c) ? std::string("'") + c + "'" : "Non displayable") << std::endl;
	
	if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << i << std::endl;
	
	if (d < -std::numeric_limits<float>::max() - 1 || d > std::numeric_limits<float>::max())
		std::cout << "float: impossible" << std::endl;
	else if (d - std::floor(d) != 0.0)
		std::cout << "float: " << f << "f" << std::endl;
	else
		std::cout << "float: " << f << ".0f" << std::endl;

	if (d - std::floor(d) != 0.0)
		std::cout << "double: " << d << std::endl;
	else
		std::cout << "double: " << d << ".0" << std::endl;
}

static void print_special (const std::string &str)
{
	std::cout << "char: impossible\nint: impossible" << std::endl;

	if (str == "+inf" || str == "+inff")
		std::cout << "float: +inff\ndouble: +inf" << std::endl;
	else if (str == "-inf" || str == "-inff")
		std::cout << "float: -inff\ndouble: -inf" << std::endl;
	else if (str == "nan" || str == "nanf")
		std::cout << "float: nanf\ndouble: nan" << std::endl;
}

void ScalarConverter::convert (std::string str)
{
	if (!is_double(str) && !is_special(str))
	{
		printImpossible();
		return ;
	}

	if (is_special(str))
		return (print_special(str));

	if (is_double(str))
		return (print_double(str));	
}