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
		bool operator> (const Fixed &obj) const;
		bool operator>= (const Fixed &obj) const;
		bool operator< (const Fixed &obj) const;
		bool operator<= (const Fixed &obj) const;
		bool operator== (const Fixed &obj) const;
		bool operator!= (const Fixed &obj) const;
		Fixed operator+ (const Fixed &obj) const;
		Fixed operator- (const Fixed &obj) const;
		Fixed operator* (const Fixed &obj) const;
		Fixed operator/ (const Fixed &obj) const;
		Fixed &operator++ ();
		Fixed operator++ (int);
		Fixed &operator-- ();
		Fixed operator-- (int);
		static Fixed &min (Fixed &a, Fixed &b);
		static const Fixed &min (const Fixed &a, const Fixed &b);
		static Fixed &max (Fixed &a, Fixed &b);
		static const Fixed &max (const Fixed &a, const Fixed &b);
};

std::ostream &operator<< (std::ostream &out, const Fixed &obj);

#endif