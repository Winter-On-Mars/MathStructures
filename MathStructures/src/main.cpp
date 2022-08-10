#include <iostream>
#include <chrono>
#include <vector>
#include <optional>
#include "../Structures/MathStructs.h"

class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
	const char* m_name;
public:
	Timer(const char* name) :
		m_name(name),
		m_beg(std::chrono::high_resolution_clock::now()) { }
	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - m_beg);
		std::cout << m_name << " : " << dur.count() << " musec\n";
	}
};
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

	// timer 1
	{
		Timer timer("m1");
		t1 = m1.inverse();
	}

	// timer 2
	{
		Timer timer("m2");
		t2 = m2.inverse();
	}

	// timer 3
	{
		Timer timer("m3");
		t3 = m3.inverse();
	}

	return 0;
}