#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>

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

		Fixed (const int value);
		Fixed (const float value);
		float toFloat( void ) const;
		int toInt( void ) const;

		int getRawBits( void ) const;
		void setRawBits( int const raw );
		Fixed &operator< (const Fixed &obj);
		Fixed &operator> (const Fixed &obj);
		Fixed &operator>= (const Fixed &obj);
		Fixed &operator<= (const Fixed &obj);
		Fixed &operator== (const Fixed &obj);
		Fixed &operator!= (const Fixed &obj);
};

std::ostream &operator<< (std::ostream &out, const Fixed &obj);

#endif