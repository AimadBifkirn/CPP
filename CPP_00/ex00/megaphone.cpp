#include <iostream>

void	uper_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		std::cout << (char)toupper(str[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
		return (0);
	}
	while (argv[i])
	{
		uper_print(argv[i]);
		i++;
	}
	std::cout << "\n";
	return (0);
}
