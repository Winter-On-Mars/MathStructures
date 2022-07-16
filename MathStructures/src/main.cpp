#include <iostream>
#include "../Structures/MathStructs.h"

double func(int i) {
	return i * i;
}

int main() {
	std::cout << "Hello World!\n";
	
	safe::gift<double> test(20);

	std::cout << test.unwrap() << "\n";

	std::cout << "readable text\n";

	return 0;
}