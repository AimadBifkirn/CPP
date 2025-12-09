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


static bool isChar(const std::string &s)
{
    return (s.length() == 1 && !std::isdigit(s[0]));
}

static bool isInt(const std::string &s)
{
    if (s.empty())
        return false;

    int i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;

    if (i == (int)s.length())
        return false;

    for (; i < (int)s.length(); i++)
        if (!std::isdigit(s[i]))
            return false;

    return true;
}

static bool isFloat(const std::string &s)
{
    if (s.empty() || s[s.length() - 1] != 'f')
        return false;

    int i = 0, dot = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (; i < (int)s.length() - 1; i++)
    {
        if (s[i] == '.')
        {
            if (dot || i == 0 || s[i + 1] == 'f')
				return (false);
            dot = 1;
        }
        else if (!std::isdigit(s[i]))
            return (false);
    }
    return (true);
}

static bool isDouble(const std::string &s)
{
    if (s.empty() || s[s.length() - 1] == 'f')
        return false;

    int i = 0, dot = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (; i < (int)s.length(); i++)
    {
        if (s[i] == '.')
        {
            if (dot || i == 0 || s[i + 1] == '\0')
				return (false);
            dot = 1;
        }
        else if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

static bool is_special (const std::string &str)
{
	return (str == "-inff" || str == "+inff" || str == "nanf" || str == "-inf" || str == "+inf" || str == "nan");
}

static int get_type (const std::string &str)
{
	if (isChar(str))
		return 'c';
	else if (isInt(str))
		return 'i';
	else if (isFloat(str))
		return 'f';
	else if (isDouble(str))
		return 'd';
	else if (is_special(str))
		return 's';
	else
		return -1;
}

static void printImpossible ()
{
	std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
}

static void print_all(const std::string &str, int type)
{
	std::istringstream toConvert(str);
	double d;

	if (type == 'c')
	{
		char c = str[0];
		d = static_cast<double>(c);
	}
	else
	{
		toConvert >> d;
		if (toConvert.fail())
		{
			return printImpossible();
		}
	}
	char c = static_cast<char>(d);
	int i = static_cast<int>(d);
	float f = static_cast<float>(d);
	(void)type;
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
	int type = get_type(str);
	if (type == -1)
	{
		printImpossible();
		return ;
	}

	if (type == 's')
		return (print_special(str));

	return (print_all(str, type));
}