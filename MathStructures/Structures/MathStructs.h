#ifndef MathStructs
#define MathStructs

#include <iostream>
#include <iomanip>
#include <string>
#include <optional>

/*
	TODO:
	add matrix reduced echelon form
	add matrix inverses
	integrate std::optional
*/

namespace math {
	class Complex;
	class Matrix;
	class Vector;

	// essentially just a struct -\_(-_-)_/-
	class Complex {
	public:
		double real;
		double complex;

		Complex();
		Complex(const double& r, const double& c);
		Complex(const Complex& Z);
		// Complex(const safe::gift<Complex>& Z);
		~Complex();
		/*
			returns a 2x2 matrix with entries representing
			the complex number as a transform
		*/
		math::Matrix toMatrix();
		double mod();
		double arg();
		Complex operator+ (const Complex& z);
		// friend functions seem to have to be defined in the class
		friend Complex operator* (const double& d, const Complex& z) {
			return Complex(d * z.real, d * z.complex);
		}
		Complex operator* (const Complex& z);
		/*
			prints the complex number to the standard output in the form
			(z.real) + (z.complex) i
		*/
		friend std::ostream& operator<< (std::ostream& output, const Complex& z) {
			output << z.real << " + " << z.complex << "i\n";
			return output;
		}
	};

	class Matrix {
	public:
		 int rows;
		 int cols;
		 int dims;
		 double** elements;

		Matrix();
		Matrix(const int& r, const int& c);
		Matrix(const Matrix& m);
		Matrix(Matrix&& m) noexcept;
		Matrix(const int& r, const int& c, const double* arr);
		Matrix(const Vector& v);
		~Matrix();
		// multiplies m1 with m2
		static Matrix identity(const int& s);
		static Matrix matmult(const Matrix& m1, const Matrix& m2);
		// return an upper triangular matrix based on the matrix passed in
		static Matrix triangular(const Matrix& m);
		Matrix matmult(const Matrix& m);
		// reduces the first matrix to row echelon
		// applying the same operations to m2
		Matrix rowEchelon(const Matrix& m1, const Matrix& m2);
		// returns the inverse of the matrix if it exists
		Matrix inverse();
		// currently only works with square matrices
		Matrix transpose();
		// this function has an error where if you input invalid numbers
		// then the function will return 0
		// this is a known bug
		double operator() (const  int& r, const  int& c);
		// this function has an error where if you input invalid numbers
		// then the function will return 0
		// this is a known bug
		double operator() (const  int& r, const  int& c) const;
		double* operator[] (const int& r);
		double* operator[] (const int& r) const;
		friend Matrix operator* (const double& d, const Matrix& m) {
			math::Matrix rmat = math::Matrix(m.cols, m.rows);
			for ( int i = 0; i < rmat.rows; i++) 
				for ( int j = 0; j < rmat.cols; j++)
				rmat.elements[i][j] = d * m(i, j);
			return rmat;
		}
		Matrix operator* (const Matrix&);
		Vector operator* (const Vector&);
		Matrix operator+ (const Matrix&);
		Matrix operator- (const Matrix&);
		void operator= (const Matrix&);
		/*
		* prints the matrix to the standard output in the form
		* | a[0][0] a[0][1] ... a[0][a.size - 1] |
		* | a[1][0] a[1][1] ... a[1][a.size - 1] |
		* | ...                                  |
		* | a[a.size - 1][0] a[a.size - 1][1] ... a[a.size - 1][a.size - 1] |\n
		*/
		friend std::ostream& operator<< (std::ostream& output, const Matrix& M) {
			for (int i = 0; i < M.cols; i++) 
				output << "---------------";
			output << '\n';
			for ( int i = 0; i < M.rows; i++) {
				output << "|";
				for ( int j = 0; j < M.cols; j++) {
					output << std::left << std::setw(15) << std::setfill(' ') << M.elements[i][j];
				}
				output << "|\n";
			}
			for (int i = 0; i < M.cols; i++) 
				output << "---------------";
			output << '\n';
			return output;
		}
	};

	class Vector {
	public:
		 int size;
		 double* elm;

		Vector();
		Vector(const int& s);
		Vector(const int& s, const double* arr);
		Vector(const int& s, double (*func)(double x));
		Vector(const Vector& v);
		~Vector();
		double operator[] (const  int& i);
		double operator[] (const int& i) const;
		Vector operator* (const double& d);
		friend Vector operator* (const double& d, const Vector& V) {
			Vector rvec = Vector(V.size);
			for ( int i = 0; i < rvec.size; i++)
				rvec.elm[i] = V.elm[i] * d;
			return rvec;
		}
		double operator* (const Vector& v);
		Vector operator+ (const Vector& v);
		Vector operator- (const Vector& v);
		/*
		* prints the vector to the standard output in the form
		* < v[0], v[1], ... , v[v.size - 1] >\n
		*/
		friend std::ostream& operator<< (std::ostream& output, const Vector& v) {
			output << "<";
			for ( int i = 0; i < v.size; i++)
				output << ' ' << v.elm[i] << ((i == v.size - 1) ? " " : ", ");
			output << ">\n";
			return output;
		}
	};
}

#endif // !MathStructs
