#include "bigint.hpp"

bigint::bigint() {}

bigint::bigint(const char* nbr)
{
	int len = 0;
	int current_pos = 999;

	for (int n = 0; n < 1000; n++)   // ft_bzero;
		tab[n] = 0;

	while (nbr[len])
		len++;

	for (int i = len - 1; i >= 0; i--)
	{
		tab[current_pos] = nbr[i] - '0';
		current_pos--;
	}
}

bigint::bigint(unsigned int nbr)
{
	int i = 999;

	for (int n = 0; n < 1000; n++)  // ft_bzero;
		tab[n] = 0;

	while (nbr > 10)
	{
		tab[i] = nbr % 10;
		nbr /= 10;
		i--;
	}
	tab[i] = nbr;
}

bigint::bigint(const bigint& other)
{
	for (int i = 0; i < 1000; i++)
		tab[i] = other.tab[i];
}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		for (int i = 0; i < 1000; i++)
			tab[i] = other.tab[i];
	return *this;
}

bigint::~bigint() {}

bigint bigint::operator+(const bigint& other)
{
	int carry = 0;
	bigint result;

	for (int i = 999; i >= 0; i--)
	{
		int sum = tab[i] + other.tab[i] + carry;
		result.tab[i] = sum % 10;
		carry = sum / 10;
	}
	return result;
}

bigint& bigint::operator+=(const bigint& other)
{
	int carry = 0;

	for (int i = 999; i >= 0; i--)
	{
		int sum = tab[i] + other.tab[i] + carry;
		tab[i] = sum % 10;
		carry = sum / 10;
	}
	return *this;
}

bigint bigint::operator<<(int n)
{
	bigint result;

	for (int i = 0; i <= 999; i++)
	{
		if (i - n >= 0)
			result.tab[i - n] = tab[i];
	}
	return result;
}

bigint& bigint::operator<<=(int n)
{
	for (int i = 0; i <= 999; i++)
	{
		if (i - n >= 0)
			tab[i - n] = tab[i];
		tab[i] = 0;
	}
	for (int i = 1000 - n; i < 1000; i++)
	{
		if (i >= 0)
			tab[i] = 0;
	}
	return *this;
}

bigint bigint::operator>>(int n)
{
	bigint result;

	for (int i = 0; i <= 999; i++)
	{
		if (i + n <= 999)
			result.tab[i + n] = tab[i];
	}
	return result;
}

bigint& bigint::operator>>=(int n)
{
	for (int i = 999; i >= 0; i--)
	{
		if (i + n <= 999)
			tab[i + n] = tab[i];
	}
	for (int i = 0; i < n && i < 1000; i++)
		tab[i] = 0;
	return *this;
}
