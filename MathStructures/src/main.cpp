#include <iostream>
// #include <chrono>
#include <vector>
#include <optional>
#include "../Structures/MathStructs.h"

// how to get time
// std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
// std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
// std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
// std::cout << duration.count() << '\n';

// we can probably do this by passing in a math::vector
// math::Matrix m(2, 2, { 1.0, 0.0, 0.0, 1.0 });

int main() {
	int s1 = 2;
	int s2 = 3;
	int s3 = 4;
	double arr1[] = {
		2, 3,
		5, 2
	};
	double arr2[] = {
		1, 3, 2,
		3, 1, 4,
		1, 3, 3
	};
	double arr3[] = { 
		2, 3, 1, 5,
		2, 4, 2, 4,
		4, 1, 0, 2,
		2, 6, 6, 2
	};
	math::Matrix m1(s1, s1, arr1);
	math::Matrix m2(s2, s2, arr2);
	math::Matrix m3(s3, s3, arr3);

	std::cout << "original\n" << m1 << m2 << m3;

	math::Matrix t1(s1, s1);
	math::Matrix t2(s2, s2);
	math::Matrix t3(s3, s3);
	
	t1 = m1.inverse();
	t2 = m2.inverse();
	t3 = m3.inverse();

	std::cout << "testing 1\n";
	std::cout <<  (m1 * t1);
	std::cout <<  (t1 * m1);

	std::cout << "testing 2\n";
	std::cout <<  (m2 * t2);
	std::cout <<  (t2 * m2);
	
	std::cout << "testing 3\n";
	std::cout <<  (m3 * t3);
	std::cout <<  (t3 * m3);
	return 0;
}