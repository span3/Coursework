/* Steven Pan span3@ucsc.edu	

Homework 1  CMPS109  Ira Pohl ?Due 11pm. April 8, 2013
	
	Rewrite the given C code into  Modern C++
	Properly comment changes made
	Avoid use of the preprocessor
	Use C++ IO
	Use the std namespace
	The code should be runnable using the instructional computers gnu compiler g++  
	
	Josephine Coder    April 4    to be converted to
    modern C++ code

*/
    #include <iostream> /* Imports the IO */
    #include <stdio.h> 
    #include <cmath> /* C++ version of math.h */

    using namespace std;

    double fcn(double x)
    { return x * x - 1; }
    double fcn2(double x)
    { return x * x * x * x * x - exp( x ) -2; }

    double root_find(
        double f(double),   /* function with root */
        double a, double b, /* interval (a, b) with root */
        double eps,         /* accuracy */
        double &root        /* root --output <- This is now passed into the function as a pointer */
     )
    {
        if ( b - a  < eps){
            root = (b + a)/2.0; /* all instances of root are changed now that we pass in the pointer */
            return f(root);
        }
        else
		if ( f(a)* f( (b + a)/2) <= 0)
            return root_find(f, a, (b+a)/2, eps, root);
        else
            return root_find(f, (b+a)/2, b, eps, root);
    }
    int main(void)
    {
        double x;
        cout << "Root Finder\n";
        root_find(fcn, 0.0,  4.0, 0.00001, x);
        cout << "root is at " << x << " with residual " << fcn(x) << "\n";
        root_find(fcn2, 0.0,  14.0, 0.00001, x);
        cout << "root is at " << x << "\n";
        return 0;
    }
