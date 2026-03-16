#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>

class bigint
{
	public:
		bigint();
		bigint(const char* nbr);
		bigint(unsigned int nbr);
		bigint(const bigint& other);
		bigint& operator=(const bigint& other);
		~bigint();

		int tab[1000];
		bigint operator+(const bigint& other);
		bigint& operator+=(const bigint& other);
		bigint operator<<(int n);
		bigint& operator<<=(int n);
		bigint operator>>(int n);
		bigint& operator>>=(int n);
};

inline std::ostream& operator<<(std::ostream& os, const bigint& nbr)
{
	int i = 0;

	while (i < 999 && nbr.tab[i] == 0)
		i++;

	while (i < 1000)
	{
		os << nbr.tab[i];
		i++;
	}
	return os;
}

#endif