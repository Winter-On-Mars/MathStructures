#ifndef MathStructs
#define MathStructs

#include <iostream>
#include <string>

/*
	TODO:
	integrate the safe::gift struct into the system
	add matrix multiplication 
	add matrix reduced echelon form
	add matrix inverses
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
		unsigned int errorNum;
		std::string errorHelp;
		// no copy constructor allowed
		error(const error& e) = delete;
	public:
		error(unsigned int eNum) : errorNum(eNum) {
			// will be expanded as we run into more 
			// issues
			switch (eNum) {
			case 0:
				errorHelp = "No issue";
			case 1:
				errorHelp = "Missing Value";
			}
		}
		error(unsigned int eNum, std::string e) : errorNum(eNum), errorHelp(e) { }
		error(std::string e) : errorNum(1), errorHelp(e) { }
		unsigned int getNum() { return this->errorNum; }
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

namespace safe {
	template<class T>
	struct gift {
		const T okay;
		const math::error err;
		gift(T v) : okay(v), err(0) { }

		gift() : okay(0), err(1) { }
		
		// sees if theres an error
		// if there is then the program terminates
		// otherwise it returns the okay value
		T unwrap() { err(); return okay; }

		// the same as calling ok()
		bool operator() () { return err(); }
	};
}

namespace math {
	using uint = unsigned int;

	class Complex;
	class Matrix;
	class Vector;

	class Complex {
	public:
		double real;
		double complex;

		Complex();
		Complex(double r, double c);
		Complex(const Complex& Z);
		Complex(const safe::gift<Complex>& Z);
		~Complex();
		/*
			returns a 2x2 matrix with entries representing
			the complex number as a transform
		*/
		math::Matrix toMatrix();
		operator double() const;
		Complex operator+ (const Complex& z);
		friend Complex operator* (const double& d, const Complex& z);
		Complex operator* (const Complex& z);
		/*
			prints the complex number to the standard output in the form
			(z.real) + (z.complex) i
		*/
		friend std::ostream& operator<< (std::ostream& output, const Complex& z);
	};

	class Matrix {
	public:
		uint rows;
		uint cols;
		uint dims;
		double** elements;

		Matrix();
		Matrix(uint c, uint r);
		Matrix(const Matrix& m);
		~Matrix();
		double operator() (uint c, uint r);
		double operator() (uint c, uint r) const;
		friend Matrix operator* (const double& d, const Matrix& m);
		/*
		* prints the matrix to the standard output in the form
		* | a[0][0] a[0][1] ... a[0][a.size - 1] |
		* | a[1][0] a[1][1] ... a[1][a.size - 1] |
		* | ...                                  |
		* | a[a.size - 1][0] a[a.size - 1][1] ... a[a.size - 1][a.size - 1] | 
		*/
		friend std::ostream& operator<< (std::ostream& output, const Matrix& M);
	};

	class Vector {
	public:
		uint size;
		double* elm;

		Vector();
		Vector(uint s);
		Vector(uint s, double (*func)(int i));
		Vector(const Vector& v);
		~Vector();
		double operator[] (const uint& i);
		Vector operator* (const double& d);
		friend Vector operator* (const double& d, const Vector& V);
		double operator* (const Vector& v);
		friend double operator* (const Vector& v1, const Vector& v2);
		friend std::ostream& operator<< (std::ostream& output, const Vector& v);
	};
}

#endif // !MathStructs
