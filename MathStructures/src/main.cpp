#include <iostream>
#include <chrono>
#include <vector>
#include "../Structures/MathStructs.h"

// how to get time
// std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
// std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
// std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
// std::cout << duration.count() << '\n';

// we can probably do this by passing in a math::vector
// math::Matrix m(2, 2, { 1.0, 0.0, 0.0, 1.0 });

int main() {
	{
		double m1arr[] = { 1, 2, 3, 4 };
		double m2arr[] = { 5, 4, 3, 2 };
		math::Matrix m1(2, 2, m1arr);
		math::Matrix m2(2, 2, m2arr);

		std::cout << m1 + m2 << m1 - m2;
	}

	{
		double v1arr[] = { 5, 4, 3, 2, 1 };
		math::Vector v1(5, v1arr);
		math::Vector v2(5,
			[](double x) -> double { return x; }
		);

		std::cout << v1 + v2 << v1 - v2;
	}

	return 0;
}