#include "bigint.hpp"

int main()
{
	bigint a("46");
	bigint b(26);
	bigint c = a;

	std::cout << "a: " << a << "\nb: " << b << "\nc: " << c << std::endl;

	a += b;
	bigint d = b << 2;
	c = d + b;
	std::cout << "\n\na: " << a << "\nb: " << b << "\nc: " << c << "\nd: " << d << std::endl;

}
