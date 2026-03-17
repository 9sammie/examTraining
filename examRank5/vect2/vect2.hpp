#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
	public:
		vect2();
		vect2(int i, int j);
		vect2(const vect2& other);
		vect2& operator=(const vect2& other);
		~vect2();

		int first;
		int second;

		int operator[](int i) const
		{
			if (i == 0)
				return first;
			return second;
		}

		int& operator[](int i)
		{
			if (i == 0)
				return first;
			return second;
		}

		vect2	operator++(int i);
		vect2&	operator++();
		vect2	operator--(int i);
		vect2&	operator--();
		vect2	operator+(const vect2& other) const;
		vect2&	operator+=(const vect2& other);
		vect2	operator-(const vect2& other) const;
		vect2&	operator-=(const vect2& other);
		vect2	operator*(int i);
		bool	operator==(const vect2& other) const;
		bool	operator!=(const vect2& other) const;
		bool	operator<(const vect2& other) const;
		bool	operator>(const vect2& other) const;
};

inline std::ostream& operator<<(std::ostream& os, const vect2& nbr)
{
	os << "{" << nbr.first << ", " << nbr.second << "}";
	return os;
}

inline vect2 operator*(int i, vect2& nbr)
{
	vect2 temp;
	temp.first = nbr.first * i;
	temp.second = nbr.second * i;
	return temp;
}

#endif