#include "MathStructs.h"
#include <iostream>

math::Complex::Complex() : real(0), complex(0) { };

math::Complex::Complex(const double& r, const double& c) : real(r), complex(c) { };

math::Complex::Complex(const Complex& Z) : real(Z.real), complex(Z.complex) { };

//math::Complex::Complex(const safe::gift<math::Complex>& Z) { 
//	this->real = Z.unwrap().real;
//	this->complex = Z.unwrap().complex;
//}

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
math::Matrix::Matrix() : rows(0), cols(0), dims(0) {
	this->elements = new double* [rows];
	for ( int i = 0; i < rows; i++) {
		this->elements[i] = new double[cols] { };
	}
}

// creates a c x r D matrix, initialized with 0s
math::Matrix::Matrix(const  int& r, const  int& c) : rows(r), cols(c), dims(c * r) {
	this->elements = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->elements[i] = new double[cols] {0};
	}
}

math::Matrix::Matrix(const math::Matrix& m) : rows(m.rows), cols(m.cols), dims(m.dims) {
	this->elements = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->elements[i] = new double[cols];
		memcpy(this->elements[i], m.elements[i], cols * sizeof(double));
	}
}

math::Matrix::Matrix(const int& r, const int& c, const double* arr) : rows(r), cols(c), dims(rows * cols) {
	this->elements = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->elements[i] = new double[cols];
		for (int j = 0; j < cols; j++) 
			this->elements[i][j] = arr[i * cols + j];
		// memcpy(this->elements[i], arr, cols * sizeof(double));
	}
}

math::Matrix::~Matrix() {
	for ( int i = 0; i < rows; i++)
		delete[] elements[i];
	delete[] this->elements;
}

// naive method
// impliment cache optimized multiplication then benchmark them against eachother ? -\_(-_-)_/-
math::Matrix math::Matrix::matmult(const math::Matrix& m1, const math::Matrix& m2) {
	if (m1.cols != m2.rows) return math::Matrix();
	math::Matrix rmat = math::Matrix(m1.rows, m2.cols);
	for (int i = 0; i < rmat.rows; i++) {
		for (int j = 0; j < rmat.cols; j++) {
			double sum = 0;
			for (int k = 0; k < m1.cols; k++)
				sum += m1[i][k] * m2[k][j];
			rmat[i][j] = sum;
		}
	}
	return rmat;
}

math::Matrix math::Matrix::matmult(const math::Matrix& m) {
	if (this->cols != m.rows) return math::Matrix();
	math::Matrix rmat = math::Matrix(this->rows, m.cols);
	for (int i = 0; i < rmat.rows; i++) {
		for (int j = 0; j < rmat.cols; j++) {
			double sum = 0;
			for (int k = 0; k < this->cols; k++)
				sum += this->elements[i][k] * m[k][j];
			rmat[i][j] = sum;
		}
	}
	return rmat;
}

math::Matrix math::Matrix::identity(const  int& s) {
	math::Matrix rmat = math::Matrix(s, s);
	for (int i = 0; i < s; i++)
		rmat.elements[i][i] = 1;
	return rmat;
}

math::Matrix math::Matrix::inverse() {
	if (this->cols != this->rows) return math::Matrix();
	// have to do gaussian elimination on matrix to get inverse
	math::Matrix copy = *this;
	math::Matrix rmat = math::Matrix(this->rows, this->cols);

	// this is where we do the gaussian elimination

	return rmat;
}

// this is where the gift class would be nice
// because using null is not what i would like to do
double math::Matrix::operator() (const  int& r, const  int& c) {
	if (this->elements == nullptr || this->elements[r] == nullptr)
		return NULL;
	if (r < 0 || r > this->rows)
		return NULL;
	if (c < 0 || c > this->cols)
		return NULL;
	return this->elements[r][c];
}

double math::Matrix::operator() (const  int& r, const  int& c) const {
	if (this->elements == nullptr || this->elements[r] == nullptr)
		return NULL;
	if (r < 0 || r > this->rows)
		return NULL;
	if (c < 0 || c > this->cols)
		return NULL;
	return this->elements[r][c];
}

double* math::Matrix::operator[] (const int& r) { 
	return (r < 0 || r > this->rows) ? nullptr : this->elements[r];
}

double* math::Matrix::operator[] (const int& r) const {
	return (r < 0 || r > this->rows) ? nullptr : this->elements[r];
}

math::Matrix math::operator* (const double& d, const math::Matrix& m) {
	math::Matrix rmat = math::Matrix(m.cols, m.rows);
	for ( int i = 0; i < rmat.rows; i++)
		for ( int j = 0; j < rmat.cols; j++)
			rmat.elements[i][j] = d * m(i, j);
	return rmat;
}

math::Matrix math::Matrix::operator*(const math::Matrix& m) {
	if (this->cols != m.rows) return math::Matrix();
	math::Matrix rmat = math::Matrix(this->rows, m.cols);
	for (int i = 0; i < rmat.rows; i++) {
		for (int j = 0; j < rmat.cols; j++) {
			double sum = 0;
			for (int k = 0; k < this->cols; k++)
				sum += this->elements[i][k] * m[k][j];
			rmat[i][j] = sum;
		}
	}
	return rmat;
}

std::ostream& math::operator<<(std::ostream& output, const Matrix& M) {
	for ( int i = 0; i < M.rows; i++) {
		output << "|";
		for ( int j = 0; j < M.cols; j++) {
			output << ' ' << M.elements[i][j];
		}
		output << " |\n";
	}
	return output;
}

math::Vector::Vector() : size(0) {
	elm = new double[0];
}

math::Vector::Vector(const  int& s) : size(s) {
	elm = new double[size] { 0 };
}

math::Vector::Vector(const  int& s, double (*func)(double x)) {
	size = s;
	elm = new double[s] { 0 };
	for ( int i = 0; i < s; i++) {
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

double math::Vector::operator[] (const  int& i) {
	return (i < size) ? elm[i] : NULL;
}

math::Vector math::Vector::operator* (const double& d) {
	Vector rvec = Vector(this->size);
	for ( int i = 0; i < this->size; i++)
		rvec.elm[i] = this->elm[i] * d;
	return rvec;
}

math::Vector math::operator* (const double& d, const math::Vector& V) {
	Vector rvec = Vector(V.size);
	for ( int i = 0; i < V.size; i++)
		rvec.elm[i] = V.elm[i] * d;
	return rvec;
}

double math::Vector::operator*(const Vector& v) {
	double total = 0;
	 int s = (v.size < this->size) ? v.size : this->size;
	for ( int i = 0; i < s; i++)
		total += v.elm[i] * this->elm[i];
	return total;
}

double math::operator* (const Vector& v1, const Vector& v2) {
	double total = 0;
	if (v1.size != v2.size) {
		// this would be a great place for
		// the gift class if we could get that to work
		std::cout << "Incorrect dimensions";
		return 0;
	}
	for (int i = 0; i < v1.size; i++)
		total += v1.elm[i] * v2.elm[i];
	return total;
}

std::ostream& math::operator<< (std::ostream& output, const math::Vector& v) {
	output << "<";
	for ( int i = 0; i < v.size; i++)
		output << ' ' << v.elm[i] << ((i == v.size - 1) ? " " : ", ");
	output << ">\n";
	return output;
}