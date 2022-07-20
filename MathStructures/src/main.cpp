#include <iostream>
#include <chrono>
#include "../Structures/MathStructs.h"



int main() {
	std::cout << "Hello World!\n";
	
	double ihatethis[] = { 1, 1, 0, 0, 0, 1 };
	double ihatethis2electricboogoolo[] = { 1, 0, 0, 1, 0, 1 };

	math::Matrix m1 = math::Matrix(3, 2, ihatethis);
	math::Matrix m2 = math::Matrix(2, 3, ihatethis2electricboogoolo);
	
	auto start1 = std::chrono::high_resolution_clock::now();
	math::Matrix m3 = m1 * m2;
	auto stop1 = std::chrono::high_resolution_clock::now();
	auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
	
	auto start2 = std::chrono::high_resolution_clock::now();
	math::Matrix m4 = m1.matmult(m1, m2);
	auto stop2 = std::chrono::high_resolution_clock::now();
	auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

	auto start3 = std::chrono::high_resolution_clock::now();
	math::Matrix m5 = m1.matmult(m2);
	auto stop3 = std::chrono::high_resolution_clock::now();
	auto dur3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);

	std::cout << dur1.count() << '\n';
	std::cout << dur2.count() << '\n';
	std::cout << dur3.count() << '\n';

	return 0;
}