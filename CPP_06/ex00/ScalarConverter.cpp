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

	for (int idx = i; str[idx]; idx++)
	{
		if (!std::isdigit(str[idx]))
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

	int x = 0;
	int y = 0;

	for (size_t idx = i; str[idx]; idx++)
	{
		if (!y && !std::isdigit(str[idx]))
			return false;
		else if (str[idx] == '.' && !x)
			x = 1;
		else if (!std::isdigit(str[idx]) && idx != str.length() - 1)
			return false;
		else if (idx == str.length() - 1 && str[idx] != 'f')
			return false;
		y = 1;
	}
	// if (x == 0)
	// 	return false;
	return true;
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

	for (int idx = i; str[idx]; idx++)
	{
		if (!y && !std::isdigit(str[idx]))
			return false;
		else if (str[idx] == '.' && !x)
			x = 1;
		else if (!std::isdigit(str[idx]))
			return false;
		y = 1;
	}
	// if (x == 0)
	// 	return false;
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

static void print_char (const std::string &str)
{
	char c = str[0];
	int i = static_cast<int>(c);
	float f = static_cast<float>(c);
	double d = static_cast<double>(c);

	std::cout << "char: " << (std::isprint(c) ? std::string("'") + c + "'" : "Non displayable") << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
}

static void print_integer(const std::string &str)
{
	std::istringstream toConvert(str);
	int i;

	toConvert >> i;
	if (toConvert.fail())
		return printImpossible();
	char c = static_cast<char>(i);
	float f = static_cast<float>(i);
	double d = static_cast<double>(i);

	if (i < 0 || i > 127)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: " << (std::isprint(c) ? std::string("'") + c + "'" : "Non displayable") << std::endl;
	std::cout << "int: " << i << std::endl;

	std::cout << "float: " << f << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
}

static void print_float(const std::string &str)
{
	std::istringstream toConvert(str);
	float f;

	toConvert >> f;
	if (toConvert.fail())
		return printImpossible();
	char c = static_cast<char>(f);
	int i = static_cast<float>(f);
	double d = static_cast<double>(f);

	if (f < 0 || f > 127)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: " << (std::isprint(c) ? std::string("'") + c + "'" : "Non displayable") << std::endl;
	
	if (f < (float)(std::numeric_limits<int>::min()) || f > (float)(std::numeric_limits<int>::max()))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << i << std::endl;
	
	if (f - std::floor(f) != 0.0f)
		std::cout << "float: " << f << "f" << std::endl;
	else
		std::cout << "float: " << f << ".0f" << std::endl;

	if (f - std::floor(f) != 0.0f)
		std::cout << "double: " << d << std::endl;
	else
		std::cout << "double: " << d << ".0" << std::endl;
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

	if (d < 0 || d > 127)
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

void ScalarConverter::convert (const std::string &str)
{
	if (!is_char(str) && !is_float(str) && !is_double(str) && !is_integer(str) && !is_special(str))
	{
		printImpossible();
		return ;
	}

	if (is_special(str))
		return (print_special(str));
	if (is_double(str))
		return (print_double(str));	
	if (is_float(str))
		return (print_float(str));
	if (is_integer(str))
		return (print_integer(str));
	if (is_char(str))
		return (print_char(str));
}