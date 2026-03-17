#include "vect2.hpp"

vect2::vect2(): first(0), second(0) {}

vect2::vect2(int i, int j): first(i), second(j) {}

vect2::vect2(const vect2& other): first(other.first), second(other.second) {}

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		first = other.first;
		second = other.second;
	}
	return *this;
}

vect2::~vect2() {}

// post-increment
vect2 vect2::operator++(int i)
{
	vect2 temp(*this);

	first += 1;
	second += 1;
	return temp;
}

// pre-increment
vect2& vect2::operator++()
{
	first++;
	second++;
	return *this;
}

// post-increment
vect2 vect2::operator--(int i)
{
	vect2 temp(*this);

	first -= 1;
	second -= 1;
	return temp;
}

// pre-increment
vect2& vect2::operator--()
{
	first--;
	second--;
	return *this;
}

vect2 vect2::operator+(const vect2& other)
{
	vect2 result((first + other.first), (second + other.second)); 
	return result;
}

vect2& vect2::operator+=(const vect2& other)
{
	first += other.first;
	second += other.second;
	return *this;
}

vect2 vect2::operator-(const vect2& other)
{
	vect2 result((first - other.first), (second - other.second)); 
	return result;
}

vect2& vect2::operator-=(const vect2& other)
{
	first -= other.first;
	second -= other.second;
	return *this;
}

vect2 vect2::operator*(int i)
{
	vect2 temp;

	temp.first = first * i;
	temp.second = second * i;
	return temp;
}

bool vect2::operator==(const vect2& other)
{
	if (first == other.first && second == other.second)
		return 1;
	return 0;
}

bool vect2::operator!=(const vect2& other)
{
	if (first != other.first || second != other.second)
		return 1;
	return 0;
}

bool vect2::operator<(const vect2& other)
{
	if (first < other.first && second < other.second)
		return 1;
	return 0;
}

bool vect2::operator>(const vect2& other)
{
	if (first > other.first && second > other.second)
		return 1;
	return 0;
}

// ##############################################################
// ##################### const version ##########################
// ##############################################################

vect2 vect2::operator+(const vect2& other) const
{
	vect2 result((first + other.first), (second + other.second)); 
	return result;
}

vect2 vect2::operator-(const vect2& other) const
{
	vect2 result((first - other.first), (second - other.second)); 
	return result;
}

bool vect2::operator==(const vect2& other) const
{
	if (first == other.first && second == other.second)
		return 1;
	return 0;
}

bool vect2::operator!=(const vect2& other) const
{
	if (first != other.first || second != other.second)
		return 1;
	return 0;
}

bool vect2::operator<(const vect2& other) const
{
	if (first < other.first && second < other.second)
		return 1;
	return 0;
}

bool vect2::operator>(const vect2& other) const
{
	if (first > other.first && second > other.second)
		return 1;
	return 0;
}