#include "main.hpp"
#include "PhoneBook.hpp"

int safe_atoi(const std::string& str, bool& ok) {
    std::istringstream iss(str);
    int value;
    if (iss >> value) {
        ok = true;
        return value;
    }
    ok = false;
    return 0; 
}

void	search(PhoneBook &pb)
{
	std::string	search_input;
	int			converted;
	bool		ok;

	if (pb.displayContacts())
		return ;
	std::cout << "Enter the index of the contact you're looking for: ";
	if (!std::getline(std::cin, search_input))
	{
		std::cout << "\nEOF detected, exiting ...\n";
		exit(0);
	}
	safe_atoi(search_input, ok);
	if (ok)
		converted = std::atoi(search_input.c_str());
	else
		converted = 0;
	while (converted < 1 || converted > 8)
	{
		std::cout << "\033[31mERROR:\033[0m Index must be a digite and between 1 and 8\n";
		std::cout << "Enter the index of the contact you're looking for: ";
		if (!std::getline(std::cin, search_input))
		{
			std::cout << "\nEOF detected, exiting ...\n";
			exit(0);
		}
		safe_atoi(search_input, ok);
		if (ok)
			converted = std::atoi(search_input.c_str());
		else
			converted = 0;
	}
	pb.getContact(converted - 1);
}

std::string	ask_for_input(std::string str)
{
	std::string	input;

	std::cout << str;
	if (!std::getline(std::cin, input))
	{
		std::cout << "\nEOF detected, exiting ...\n";
		exit(0);
	}
	while (input.empty() || std::isspace(input[0]))
	{
		std::cout << "\033[31mERROR:\033[0m A saved contact can’t have empty fields\n" << str;
		if (!std::getline(std::cin, input))
		{
			std::cout << "\nEOF detected, exiting ...\n";
			exit(0);
		}
	}
	return (input);
}

void	add_contact(PhoneBook &pb)
{
	Contact	new_contact;

	new_contact.set_first_name(ask_for_input("first name : "));
	new_contact.set_last_name(ask_for_input("last name : "));
	new_contact.set_nickname(ask_for_input("nickname : "));
	new_contact.set_phone_number(ask_for_input("phone number : "));
	new_contact.set_darkest_secret(ask_for_input("darkest secre : "));
	pb.add(new_contact);
}

void	process_input(std::string input, PhoneBook &pb)
{	
	if (input == "EXIT")
		exit(0);
	else if (input == "ADD")
		add_contact(pb);
	else if (input == "SEARCH")
		search(pb);
	else
		std::cout << "\033[31mERROR:\033[0m Invalid command\n";
}

int	main()
{
	PhoneBook	pb;
	std::string	input;
	while (1)
	{
		std::cout << "enter a command (ADD, SEARCH, EXIT) : ";
		if (!std::getline(std::cin, input, '\n'))
		{
			std::cout << "\nEOF detected, exiting ...\n";
			return (0);
		}
		process_input(input, pb);
	}
	return (0);
}
