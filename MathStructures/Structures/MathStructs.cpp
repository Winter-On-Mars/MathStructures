#include "MathStructs.h"
#include <iostream>
#include <cmath>
#include <cstring>
#define abs(x) ((x < 0) ? -x : x)
#define DEBUG false

math::Complex::Complex() : real(0), complex(0) { };

math::Complex::Complex(const double& r, const double& c) : real(r), complex(c) { };

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

double math::Complex::mod() { 
	return std::sqrt(this->real * this->real + this->complex * this->complex); 
}

double math::Complex::arg() { 
	return std::atan(this->complex / this->real); 
}

math::Complex math::Complex::operator+ (const Complex& z) {
	return Complex(this->real + z.real, 
		this->complex + z.complex
	);
}

math::Complex math::Complex::operator* (const Complex& z) {
	return Complex(
		this->real * z.real - this->complex * z.complex,
		this->real * z.complex - this->complex * z.real
	);
}
	
// creates a 0D matrix
math::Matrix::Matrix() : rows(0), cols(0), dims(0) {
	this->elements = new double* [rows];
	for ( int i = 0; i < rows; i++) {
		this->elements[i] = new double[cols] { };
	}
}

// creates a r x c D matrix, initialized with 0s
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

math::Matrix::Matrix(math::Matrix&& m) noexcept : rows(std::move(m.rows)), cols(std::move(m.cols)), dims(std::move(m.dims)) {
	this->elements = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->elements[i] = m.elements[i];
	}

	m.cols = m.rows = m.dims = 0;
	for (int i = 0; i < rows; i++) {
		m.elements[i] = nullptr;
	}
	m.elements = nullptr;
}

math::Matrix::Matrix(const int& r, const int& c, const double* arr) : rows(r), cols(c), dims(rows * cols) {
	this->elements = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->elements[i] = new double[cols];
		// this should just be a memcpy
		for (int j = 0; j < cols; j++) 
			this->elements[i][j] = arr[i * cols + j];
		// memcpy(this->elements[i], arr, cols * sizeof(double));
	}
}

math::Matrix::Matrix(const math::Vector& v) 
	: rows(std::sqrt(v.size)), cols(rows), dims(v.size)
{
	this->elements = new double* [rows];
	for (int i = 0; i < rows; i++) {
		this->elements[i] = new double[cols];
		for (int j = 0; j < cols; j++)
			this->elements[i][j] = v[i * cols + j];
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

math::Matrix math::Matrix::identity(const int& s) {
	math::Matrix rmat = math::Matrix(s, s);
	for (int i = 0; i < s; i++)
		rmat.elements[i][i] = 1;
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

template<typename t>
void swap(t& a, t& b) {
	t temp = a;
	a = b;
	b = temp;
}

math::Matrix math::Matrix::triangular(const math::Matrix& m) {
	if (m.cols != m.rows) return math::Matrix();
	math::Matrix rmat = m;
	for (int k = 0; k < rmat.cols; k++) {
		// start in left most column 
		int maxi = k;
		// find the max in the column
		for (int i = k; i < rmat.rows; i++) {
			maxi = (abs(rmat(maxi, k)) < abs(rmat(i, k))) ? i : maxi;
		}
		// swap the row with the current elimination row
		// swap the copy of the matrix
		swap(rmat.elements[maxi], rmat.elements[k]);
		// eliminate down
		for (int i = k + 1; i < rmat.rows; i++) {
			double multfact = rmat(i, k) / rmat(k, k);
			for (int j = k; j < rmat.cols; j++) {
				rmat.elements[i][j] = rmat(i, j) - multfact * rmat(k, j);
			}
		}
	}
	return rmat;
}

// should return an optional or my own version of optional
math::Matrix math::Matrix::inverse() {
	if (this->cols != this->rows) return math::Matrix();
	// have to do gaussian elimination on matrix to get inverse
	math::Matrix cmat = *this;
	math::Matrix rmat = math::Matrix::identity(cmat.rows);
	// TODO:
	// 	impliment the pivoting gaussian elimination 
	
	// start in the left most column
	for (int k = 0; k < cmat.cols; k++) {
		// start in the top row
		for (int i = k + 1; i < cmat.rows; i++) {
			// find the multipliers
			double firstMult = cmat(k, k);
			double secondMult = -cmat(i, k);
			// eliminate the row
			for (int j = 0; j < cmat.cols; j++) {
				cmat.elements[i][j] = firstMult * cmat(i, j) + secondMult * cmat(k, j);
				rmat.elements[i][j] = firstMult * rmat(i, j) + secondMult * rmat(k, j);
			}
		}
	}

	for (int k = cmat.cols - 1, conv = 1; k > 0; k--, conv++) {
		for (int i = cmat.rows - 1 - conv; i >= 0; i--) {
			double firstMult = cmat(k, k);
			double secondMult = -cmat(i, k);
			// elim row
			for (int j = 0; j < cmat.cols; j++) {
				cmat.elements[i][j] = firstMult * cmat(i, j) + secondMult * cmat(k, j);
				rmat.elements[i][j] = firstMult * rmat(i, j) + secondMult * rmat(k, j);
			}
		}
	}

	// rescale
	for (int i = 0; i < cmat.rows; i++) {
		double factor = 1 / cmat(i, i);
		for (int j = 0; j < cmat.cols; j++) {
			cmat.elements[i][j] = factor * cmat(i, j);
			rmat.elements[i][j] = factor * rmat(i, j);
		}
	}
	return rmat;
}

math::Matrix math::Matrix::transpose() {
	math::Matrix rmat(this->rows, this->cols);
	for (int i = 0; i < rmat.rows; i++) {
		for (int j = 0; j < rmat.cols; j++) {
			rmat.elements[i][j] = this->elements[j][i];
		}
	}
	return rmat;
}

// this is where the gift class would be nice
// because using null is not what i would like to do
double math::Matrix::operator() (const  int& r, const  int& c) {
	if (this->elements == nullptr || this->elements[r] == nullptr)
		return 0;
	if (r < 0 || r > this->rows)
		return 0;
	if (c < 0 || c > this->cols)
		return 0;

	return this->elements[r][c];
}

double math::Matrix::operator() (const  int& r, const  int& c) const {
	if (this->elements == nullptr || this->elements[r] == nullptr)
		return 0;
	if (r < 0 || r > this->rows)
		return 0;
	if (c < 0 || c > this->cols)
		return 0;

	return this->elements[r][c];
}

double* math::Matrix::operator[] (const int& r) { 
	return (r < 0 || r > this->rows) ? nullptr : this->elements[r];
}

double* math::Matrix::operator[] (const int& r) const {
	return (r < 0 || r > this->rows) ? nullptr : this->elements[r];
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

math::Vector math::Matrix::operator* (const Vector& v) {
	if (this->cols != v.size) return math::Vector();
	math::Vector rvec = math::Vector(this->rows);
	for (int i = 0; i < this->rows; i++) {
		double sum = 0;
		for (int j = 0; j < this->cols; j++) {
			sum += this->elements[i][j] * v.elm[j];
		}
		rvec.elm[i] = sum;
	}
	return rvec;
}

math::Matrix math::Matrix::operator+ (const Matrix& m) {
	if (this->cols != m.cols && this->rows != m.rows) return math::Matrix();
	math::Matrix rmat = math::Matrix(this->cols, this->rows);
	for ( int i = 0; i < rmat.rows; i++ ) 
		for ( int j = 0; j < rmat.cols; j++ ) 
			rmat.elements[i][j] = (*this)(i, j) + m(i, j);
	return rmat;
}

math::Matrix math::Matrix::operator- (const Matrix& m) {
	if (this->cols != m.cols && this->rows != m.rows) return math::Matrix();
	math::Matrix rmat = math::Matrix(this->cols, this->rows);
	for ( int i = 0; i < rmat.rows; i++ ) 
		for ( int j = 0; j < rmat.cols; j++ )
			rmat.elements[i][j] = (*this)(i, j) - m(i, j);
	return rmat;
}

void math::Matrix::operator= (const Matrix& m) {
	if (this->cols != m.cols || this->rows != m.rows) return;
	for (int i = 0; i < this->rows; i++) {
		memcpy(this->elements[i], m.elements[i], m.cols * sizeof(double));
	}
}

math::Vector::Vector() : size(0) {
	elm = new double[0];
}

math::Vector::Vector(const  int& s) : size(s) {
	elm = new double[size] { 0.0 };
}

math::Vector::Vector(const int& s, const double* arr) : size(s) {
	elm = new double[size] { 0.0 };
	memcpy(elm, arr, size * sizeof(double));
}

math::Vector::Vector(const  int& s, double (*func)(double x)) {
	size = s;
	elm = new double[s] { 0.0 };
	for ( int i = 0; i < s; i++ ) {
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

// these should probably throw an error instead but -\_(-_-)_/-
double math::Vector::operator[] (const  int& i) {
	return (i < size) ? elm[i] : 0;
}

double math::Vector::operator[] (const int& i) const {
	return (i < size) ? elm[i] : 0;
}

math::Vector math::Vector::operator* (const double& d) {
	Vector rvec = Vector(this->size);
	for ( int i = 0; i < this->size; i++)
		rvec.elm[i] = this->elm[i] * d;
	return rvec;
}

double math::Vector::operator*(const Vector& v) {
	double total = 0;
	int s = (v.size < this->size) ? v.size : this->size;
	for ( int i = 0; i < s; i++)
		total += v.elm[i] * this->elm[i];
	return total;
}

math::Vector math::Vector::operator+ (const Vector& v) {
	if (this->size != v.size) return Vector();
	math::Vector rvec = Vector(this->size);
	for ( int i = 0; i < rvec.size; i++ )
		rvec.elm[i] = (*this)[i] + v[i];
	return rvec;
}

math::Vector math::Vector::operator- (const Vector& v) {
	if (this->size != v.size) return Vector();
	math::Vector rvec = Vector(this->size);
	for ( int i = 0; i < rvec.size; i++ )
		rvec.elm[i] = (*this)[i] - v[i];
	return rvec;
}
