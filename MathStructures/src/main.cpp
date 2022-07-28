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
	double m1arr[] = { 1, 2, 3, 4 };
	double m2arr[] = { 5, 4, 3, 2 };
	math::Matrix m1(2, 2, m1arr);
	math::Matrix m2(2, 2, m2arr);

	math::Matrix m3 = m1 * m2;
	math::Matrix m4 = m1.matmult(m2);
	math::Matrix m5 = math::Matrix::matmult(m1, m2);

	std::cout << m3 << m4 << m5;

	return 0;
}