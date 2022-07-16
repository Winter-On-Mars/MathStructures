#include "MathStructs.h"
#include <iostream>

math::Complex::Complex() : real(0), complex(0) { };

math::Complex::Complex(double r, double c) : real(r), complex(c) { };

math::Complex::Complex(const Complex& Z) : real(Z.real), complex(Z.complex) { };

math::Complex::~Complex() { };
		
math::Matrix math::Complex::toMatrix() {
	math::Matrix rm = math::Matrix(2, 2);
	rm.elements[0][0] = this->real;
	rm.elements[0][1] = -this->complex;
	rm.elements[1][0] = this->complex;
	rm.elements[1][1] = this->real;
	return rm;
}

math::Complex::operator double() const {
	return 0;
}

math::Complex math::Complex::operator+ (const Complex& z) {
	return Complex(this->real + z.real, 
		this->complex + z.complex
	);
}

math::Complex math::operator* (const double& d, const Complex& z) {
	return Complex(d * z.real, d * z.complex);
}

math::Complex math::Complex::operator* (const Complex& z) {
	return Complex(
		this->real * z.real - this->complex * z.complex,
		this->real * z.complex - this->complex * z.real
	);
}
	
std::ostream& math::operator<<(std::ostream& output, const Complex& z) {
	output << z.real << " + " << z.complex << "i\n";
	return output;
}
	
// creates a 0D matrix
math::Matrix::Matrix() {
	this->rows = 0;
	this->cols = 0;
	this->dims = 0;
	this->elements = new double* [cols];
	for (uint i = 0; i < cols; i++) {
		this->elements[i] = new double[rows] { };
	}
}

// creates a c x r D matrix, initialized with 0s
math::Matrix::Matrix(uint c, uint r) : rows(r), cols(c), dims(c * r) {
	this->elements = new double* [cols];
	for (uint i = 0; i < cols; i++) {
		this->elements[i] = new double[rows] {0};
	}
}

math::Matrix::Matrix(const math::Matrix& m) : rows(m.rows), cols(m.cols), dims(m.dims) {
	this->elements = new double* [cols];
	for (uint i = 0; i < cols; i++) {
		this->elements[i] = new double[rows];
		memcpy(this->elements[i], m.elements[i], rows * sizeof(double));
	}
}

math::Matrix::~Matrix() {
	for (uint i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] this->elements;
}
		
// returns the entry at the with the 
// column being the first entry and the
// row being the second
double math::Matrix::operator() (uint c, uint r) {
	if (this->elements == nullptr || this->elements[c] == nullptr)
		return NULL;
	if (r < 0 || r > this->rows)
		return 0;
	if (c < 0 || c > this->cols)
		return 0;
	return this->elements[c][r];
}

double math::Matrix::operator() (uint c, uint r) const {
	if (this->elements == nullptr || this->elements[c] == nullptr)
		return NULL;
	if (r < 0 || r > this->rows)
		return 0;
	if (c < 0 || c > this->cols)
		return 0;
	return this->elements[c][r];
}

math::Matrix math::operator* (const double& d, const math::Matrix& m) {
	math::Matrix rmat = math::Matrix(m.cols, m.rows);
	for (uint i = 0; i < rmat.cols; i++)
		for (uint j = 0; j < rmat.rows; j++)
			rmat.elements[i][j] = d * m(i, j);
	return rmat;
}

std::ostream& math::operator<<(std::ostream& output, const Matrix& M) {
	for (uint i = 0; i < M.cols; i++) {
		output << "|";
		for (uint j = 0; j < M.rows; j++) {
			output << ' ' << M.elements[i][j];
		}
		output << " |\n";
	}
	return output;
}

math::Vector::Vector() : size(0) {
	elm = new double[0];
}

math::Vector::Vector(uint s) : size(s) {
	elm = new double[size] { 0 };
}

math::Vector::Vector(uint s, double (*func)(int i)) {
	size = s;
	elm = new double[s] { 0 };
	for (uint i = 0; i < s; i++) {
		elm[i] = func(i);
	}
}

math::Vector::Vector(const math::Vector& V) : size(V.size) {
	elm = new double[V.size] { 0 };
	memcpy(elm, V.elm, V.size * sizeof(double));
}

math::Vector::~Vector() {
	delete[] elm;
}

double math::Vector::operator[] (const uint& i) {
	return (i < size) ? elm[i] : NULL;
}

math::Vector math::Vector::operator* (const double& d) {
	Vector rvec = Vector(this->size);
	for (uint i = 0; i < this->size; i++)
		rvec.elm[i] = this->elm[i] * d;
	return rvec;
	/*return Vector(size,
		[](double* arr, double d,int i) -> double { 
			return (arr[i] * d); 
		}
	);*/
}

math::Vector math::operator* (const double& d, const math::Vector& V) {
	Vector rvec = Vector(V.size);
	for (uint i = 0; i < V.size; i++)
		rvec.elm[i] = V.elm[i] * d;
	return rvec;
	
	/*return Vector(
		V.size,
		[](double* arr, double d, int i) -> double { 
			return arr[i] * d; 
		}
	);*/
}

double math::Vector::operator*(const Vector& v) {
	double total = 0;
	uint s = (v.size < this->size) ? v.size : this->size;
	for (uint i = 0; i < s; i++)
		total += v.elm[i] * this->elm[i];
	return total;
}

double math::operator* (const Vector& v1, const Vector& v2) {
	double total = 0;
	uint s = (v1.size < v2.size) ? v1.size : v2.size;
	for (uint i = 0; i < s; i++)
		total += v1.elm[i] * v2.elm[i];
	return total;
}

std::ostream& math::operator<< (std::ostream& output, const math::Vector& v) {
	output << "<";
	for (uint i = 0; i < v.size; i++)
		output << ' ' << v.elm[i] << ((i == v.size - 1) ? " " : ", ");
	output << ">\n";
	return output;
}