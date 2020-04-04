#include <iostream>
#include <gmpxx.h>

int main()
{
    mpz_class A = 300;
    mpz_class B = 360;
    std::cout << "A is: " << A << " while B is: " << B << '\n';
    // Many functions are included in the C++ interface
    std::cout << "The greatest common divisor of A and B is: " << gcd(A, B) << '\n';
    std::cout << "The absolute value of -A (-300) is: " << abs(A) << '\n';

    // With functions of the C library a simple conversion works
    mpz_class C = 2;
    std::cout << "C is: " << C << '\n';
    
    // Raise to the 65th power
    mpz_pow_ui(C.get_mpz_t(), C.get_mpz_t(), 100);
    std::cout << "C raised to the power of 100 is: " << C;
	
    return 0;
}
