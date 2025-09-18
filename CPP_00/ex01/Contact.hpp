#ifndef HEADER_HPP
#define HEADER_HPP

#include "main.hpp"

class Contact
{
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;
		std::string	phone_number;
		std::string	darkest_secret;
	public:
		std::string	get_first_name();
		std::string	get_last_name();
		std::string	get_nickname();
		std::string	get_phone_number();
		std::string	get_darkest_secret();
		void	set_first_name(std::string new_fn);
		void	set_last_name(std::string new_ln);
		void	set_nickname(std::string new_nickname);
		void	set_phone_number(std::string new_pn);
		void	set_darkest_secret(std::string new_ds);
};

#endif