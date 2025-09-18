#include "Contact.hpp"

std::string	Contact::get_first_name()
{
	return (first_name);
}

std::string	Contact::get_last_name()
{
	return (last_name);
}

std::string	Contact::get_nickname()
{
	return (nickname);
}

std::string	Contact::get_phone_number()
{
	return (phone_number);
}

std::string	Contact::get_darkest_secret()
{
	return (darkest_secret);
}

void	Contact::set_first_name(std::string new_fn)
{
	first_name = new_fn;
}

void	Contact::set_last_name(std::string new_ln)
{
	last_name = new_ln;
}

void	Contact::set_nickname(std::string new_nickname)
{
	nickname = new_nickname;
}

void	Contact::set_phone_number(std::string new_pn)
{
	phone_number = new_pn;
}

void	Contact::set_darkest_secret(std::string new_ds)
{
	darkest_secret = new_ds;
}
