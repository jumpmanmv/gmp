#include <iostream>
#include <gmpxx.h>

int main()
{
    mpz_class a ("1500000000000000000000");
    mpz_class b {"150000000000000000000"};
    std::cout << "a is: "<< a << " while b is: " << b << '\n';

    // All the usual operations can be used!
    std::cout << "The value of a + b is: " << a+b << '\n';
    std::cout << "The value of a - b is: " << a-b << '\n';
    std::cout << "The value of a * b is: " << a*b << '\n';
    std::cout << "The value of a / b is: " << a/b << '\n';
    std::cout << "The value of a % b is: " << a%b << '\n';
    std::cout << "The value of -a is: " << -a << '\n';

    // The big integers also can be intermixed with regular C/C++ types!
    mpz_class d = 10;
    int k = 34;
    std::cout << "d is a mpz_class, e is an int; d + e = " << d + k << '\n';
    double l = 3.14; 
    std::cout << "d is a mpz_class, l is a double; d + l = " << d + l << '\n';
    long long m = 2.71; 
    std::cout << "d is a mpz_class, m is a long long, so they can't be directly added;"
    " using conversion d + m = " << d + int(m) << '\n';

    // Comparisons also work!
    mpz_class e = 9;
    if (d > e) std::cout << "> works as intended" << '\n';
    if (b-1 >= e) std::cout << ">= works too" << '\n';
   
    // Intermixing with standard types works as well!
    if (d >= 8 && d < 11) std::cout << "Comparisons with standard types work!";

    return 0;
}
