#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>

class Fixed
{
	private:
		int	fp_value;
		static const int fraction;
	public:
		Fixed (); // Default constructor
		Fixed (const Fixed &other); // copy constructor
		Fixed &operator= (const Fixed &obj); // Assignment operator overload
		~Fixed (); // Destructor
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};

#endif