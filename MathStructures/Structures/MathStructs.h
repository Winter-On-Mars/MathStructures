#ifndef MathStructs
#define MathStructs

#include <iostream>
#include <string>

/*
	TODO:
	- add matrix multiplication 
	add matrix reduced echelon form
	add matrix inverses
	integrate the safe::gift struct into the system
*/

namespace math {
	/*
		general error class
		should probably be moved into
		a different namespace
		error code of 0 = no error
		error code of 1 = missing value
		honestly this should just be removed
		and i should look into using the 
		cpp error patterns
	*/
	class error {
	private:
		 int errorNum;
		std::string errorHelp;
		// no copy constructor allowed
		error(const error& e) = delete;
	public:
		error( int eNum) : errorNum(eNum) {
			// will be expanded as we run into more 
			// issues
			switch (eNum) {
			case 0:
				errorHelp = "No issue";
			case 1:
				errorHelp = "Missing Value";
			}
		}
		error( int eNum, std::string e) : errorNum(eNum), errorHelp(e) { }
		error(std::string e) : errorNum(1), errorHelp(e) { }
		 int getNum() { return this->errorNum; }
		void printError() const {
			std::cout << errorHelp;
			if (errorNum != 0) exit(errorNum);
		}
		bool operator() () {
			if (this->errorNum == 0)
				return true;
			else
				printError();
			return false;
		}
		bool operator() () const {
			if (this->errorNum == 0)
				return false;
			else
				printError();
			return true;

		}
	};
}

//namespace safe {
//	struct gift {
//		const math::Complex okay;
//		const math::error err;
//		gift(math::Complex v) : okay(v), err(0) { }
//
//		gift() : okay(math::Complex()), err(1) { }
//		
//		// sees if theres an error
//		// if there is then the program terminates
//		// otherwise it returns the okay value
//		math::Complex unwrap() { err(); return okay; }
//
//		math::Complex unwrap() const { err(); return okay; }
//
//		// the same as calling ok()
//		bool operator() () { return err(); }
//	};
//}

namespace math {
	class Complex;
	class Matrix;
	class Vector;

	class Complex {
	private:
		double r;
		double argument;
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
		// has to be called as a member of the class which feels weird
		static Matrix matmult(const Matrix& m1, const Matrix& m2);
		Matrix matmult(const Matrix& m);
		static Matrix identity(const int& s);
		Matrix rowEchelon();
		// reduces the first matrix to row echelon
		// applying the same operations to m2
		Matrix rowEchelon(const Matrix& m1, const Matrix& m2);
		// returns the inverse of the matrix if it exists
		Matrix inverse();
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
		Matrix operator* (const Matrix& m);
		Vector operator* (const Vector& v);
		Matrix operator+ (const Matrix& m);
		Matrix operator- (const Matrix& m);
		/*
		* prints the matrix to the standard output in the form
		* | a[0][0] a[0][1] ... a[0][a.size - 1] |
		* | a[1][0] a[1][1] ... a[1][a.size - 1] |
		* | ...                                  |
		* | a[a.size - 1][0] a[a.size - 1][1] ... a[a.size - 1][a.size - 1] |\n
		*/
		friend std::ostream& operator<< (std::ostream& output, const Matrix& M) {
			for ( int i = 0; i < M.rows; i++) {
				output << "|";
				for ( int j = 0; j < M.cols; j++) {
					output << ' ' << M.elements[i][j];
				}
				output << " |\n";
			}
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
