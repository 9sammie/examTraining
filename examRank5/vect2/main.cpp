#include "vect2.hpp"

int main()
{
	vect2 v1;
	const vect2 v2(1, 2);
	vect2 v3(v2);
	vect2 v4 = v3;

	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	std::cout << v4 << std::endl;
	std::cout << v1++ << std::endl;
	std::cout << ++v1 << std::endl;
	std::cout << v1-- << std::endl;
	std::cout << --v1 << std::endl;
	v1 += v2;
	v4 = v2 + v3;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v4: " << v4 << std::endl;
	v1 = v3 * 2;
	std::cout << "v1: " << v1 << std::endl;
	v1 = 4 * v1;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1[0]: " << v1[0] << std::endl;
	v1[0] = 12;
	std::cout << "v1[0]: " << v1[0] << std::endl;
}
