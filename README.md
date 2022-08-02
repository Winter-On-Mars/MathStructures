# Math Structures Overview
A simple C++ library for advanced math structures including
- Complex Numbers
- Matrices
- Vectors
## Complex Numbers
Represents complex numbers in rectangular form, with the ability to access their polar components as needes.
```
math::Complex z1(1, 1);		// represents 1 + 1i
math::Complex z2(-1, 3);	// represents -1 + 3i
math::Complex z3 = z1 + z2;
math::Complex z4 = z1 * z2;
std::cout << z1 << z2 << z3 << z4;
```
You can access the polar components with their member functions `mod()` and `arg()`, short for modulus and argument.

Yout also have the ability to transfor the complex number into a Matrix
```
math::Complex z(1, 0); // represents 1
math::Matrix m = z.toMatrix();
```
## Matrix
Creates a heap allocated 2D array of doubles to represent a matrix.
Includes a number of standard Matrix operations.
```
double m2arr[] = { 1, 2, 3, 4 };
math::Matrix m1 = math::Matrix::Identity(2);
math::Matrix m2(2, 2, m2arr);

math::Matrix m3 = m1 * m2;

std::cout << m3;
```
There is also an overload to allow matricies to be output to the standard output.
```
math::Matrix m = math::Matrix::Identity(3);
std::cout << m;
```
## Vectors
Creates a heap allocated array of doubles. 
Allows the vector to be initilized with a function pointer
```
math::Vector v(5, 
	[](double x) -> double { 
		return x; 
	}
);
```
Vectors also have overloads for the `std::cout <<` and the dot product.
# Philosophy
There are two important points about the code that is written
1. User Discipline

Most member variables are open for the user to modify themselves.

While there is syntax that allows for a safer experience, you are able to access whatever value on the object that you would like. 
Keeping the member variables open allows you to create functions in your own program to modify the objects as you would like.

2. Code Safety

All of the functions return a structure, and do not modify the original.

While this does use more RAM, especially when working with large matrices, it does help by keeping the objects essentially constant.
Just maybe don't use it on a machine with constrained memory limits.
