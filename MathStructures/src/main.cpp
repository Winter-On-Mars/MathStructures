#include <iostream>
#include "../Structures/MathStructs.h"

void func() {

}

int main() {
	std::cout << "Hello World!\n";
	
	double ihatethis[] = { 1, 2, 3, 4, 5, 6 };
	double ihatethis2electricboogoolo[] = { 10, 11, 20, 21, 30, 31 };

	math::Matrix m1 = math::Matrix(2, 3, ihatethis);
	math::Matrix m2 = m1.inverse();


	std::cout << m1;

	std::cout << "--------\n";

	std::cout << m2;

	return 0;
}