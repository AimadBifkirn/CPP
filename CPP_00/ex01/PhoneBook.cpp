#include "main.hpp"
#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	index = 0;
}

int	PhoneBook::getIndex()
{
	return(index);
}

void	print_element(std::string str)
{
	if (str.length() > 10)
		str = str.substr(0, 9) + ".";
	std::cout << std::setw(10) << str;
}

void	print_contact_infos(Contact c)
{
	std::cout << "|";
	print_element(c.get_first_name());
	std::cout << "|";
	print_element(c.get_last_name());
	std::cout << "|";
	print_element(c.get_nickname());
	std::cout << "\n";
}

int	PhoneBook::displayContacts()
{
	int	i;

	i = 0;
	if (con_arry[0].get_first_name().empty())
	{
		std::cout << "\033[31mERROR:\033[0m No contacts yet\n";
		return (1);
	}
	std::cout << "     index|first name| last name|  nickname\n";
	while (i < 8)
	{
		if (con_arry[i].get_first_name().empty())
			return (0);
		std::cout << std::setw(10) << i + 1;
		print_contact_infos(con_arry[i]);
		i++;
	}
	return (0);
}

void	PhoneBook::getContact(int i)
{
	if (con_arry[i].get_first_name().empty())
	{
		std::cout << "\033[31mERROR:\033[0m No contact with the given index\n";
		return ;
	}
	std::cout << "index      : " << i + 1 << "\nfirst name : " << con_arry[i].get_first_name() \
	<< "\nlast name  : " << con_arry[i].get_last_name() << "\nnickname   : " << con_arry[i].get_nickname() << "\n";
}

void	PhoneBook::add(Contact new_contact)
{
	con_arry[index] = new_contact;
	index++;
	if (index == 8)
		index = 0;
	std::cout << "\033[32mContact added successfully\033[0m" << std::endl;
}
