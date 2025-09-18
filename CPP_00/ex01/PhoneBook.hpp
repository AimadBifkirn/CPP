#ifndef PHONEBOOk_HPP
#define PHONEBOOk_HPP

#include "main.hpp"
#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact con_arry[8];
		int		index;
	public:
		PhoneBook();
		void	getContact(int i);
		void	add(Contact c);
		int		displayContacts();
		int		getIndex();
};


#endif