# Handle big integers in C++ using GMP


## First of all, why use GMP?
Each of the fundamental data types in C++ (and C) has a specific bit size that depends on the machine the language runs on. The number of bits allocated dictate the typical range (or in the case of a floating-point type the precision) of that data type. If a data type exceeds the maximum (or minimum) value it can hold then it overflows, resulting in wrong or undefined behavior. For example, in the standard library the largest integer possible is long long int which typically has a size of 64 bits. This means that the it can represent 2<sup>64</sup> different values, and in the case of an unsigned long long int (which doesn't support negative values) the maximum possible value is 2<sup>64-1</sup>. 2<sup>64-1</sup> is a truly large number (about 18 quintillion or 18 billion billion) and in the vast majority of cases it suffices, but there are a few cases where it doesn't. Doing computations with values higher than that is impossible using only the standard library.

Due to this specific "omission" of the C++ and C standard libraries, a number of different libraries that support bigger numbers have been created. I tried a few of them, but I usually found that they didn't have everything I wanted. I wanted a library that included at least the following features: overloaded operators, no limit on the maximum possible value, the possibility of intermixing with standard library integers, and important functions such as exponentiation or square root. This is where GMP comes in.

## What is GMP?
GMP is a library for arbitrary precision arithmetic, operating on signed integers, rational numbers, and floating-point numbers. GMP stands for GNU MultiPrecision and is part of the GNU project. Its first version was released in 1991 and it is still updated to this day. GMP uses a number of techniques in order to be as fast as possible. It is published under GNU LGPL v3 and GNU GPL v2 licenses meaning that it's completely free to use and share.

In simple words, GMP allows us to greatly extend the maximum value of integers in our programs. In fact, the practical limit is only set by the available memory in the machine GMP runs on. The C mpz_t type that stores big integers includes a whopping 150 functions! Apart from that, GMP also includes data types for rational numbers and floating-point numbers with no theoretical limits to the precision used (again the limit is set by the available memory). The basic interface of GMP is written in C but there are interfaces for other languages as well (including C++, C#, Perl, PHP, Python, and R), so you can possibly use the same library without the need to learn a completely new one for the specific language you are using.

In this guide we will be using the C++ library which is an extension of the regular C library. The GMP C++ library features a number of improvements like overloaded operators that are simply not possible in C, and although it can't directly use the entirety of the C library's functions, backwards compatibility is ensured with simple conversions.

## Installation
The library can be downloaded from the main page of GMP: https://gmplib.org. There you can also find the library's manual in HTML and PDF formats which documents everything included in the library. If you are unsure about anything regarding the library you can look it up in the manual.

GMP supports virtually all operating systems, including Windows, MacOS, and all Linux distributions. I will show the installation problem on a GNU/Linux operating system.

After downloading the archive file from the GMP page, extract it and then open a terminal inside the folder. Before we begin the installation we need to enable the installation of the C++ library since it's disabled by default. In the terminal write:
```
./configure --enable-cxx
make check
make install
```
The GMP libraries are now installed in your system. The make check command is optional but strongly suggested in order to ensure that the library works as intended. The default install locations for the libraries are /usr/local/include and /usr/local/lib.

## Using the GMP library.

As I stated above, I will be showing the C++ library of GMP, although the C library is extremely similar in usage. The library includes 3 class types:
```
The mpz_class for big integers           (the corresponding C type is mpz_t)
The mpq_class for ratios                 (the corresponding C type is mpq_t)
The mpf_class for floating-point numbers (the corresponding C type is mpf_t)
```
I will focus on the mpz_class since I assume it is the one the majority is interested in. The mpq_class and mpf_class classes follow the same structure.

Initializing an mpz_class is as simple as creating an object in a class you have created yourselves. When creating a new integer you can give it an initial value or not. Below I demonstrate different ways to create essentialy the same integer.
```
#include <iostream>
#include "gmpxx.h"

int main()
{
	// Different ways to initialize the same integer
  	// 37200000000000 is an estimation of the number of cells in the human body
	mpz_class k(37200000000000);
	mpz_class l = 37200000000000;
	mpz_class m{37200000000000};
	mpz_class n;
	n = 37200000000000;
  	long o_long = 37200000000000;
	mpz_class o(o_long);

	std::cout << "The value of k is: " << k << '\n';
	std::cout << "The value of l is: " << l << '\n';
	std::cout << "The value of m is: " << m << '\n';
	std::cout << "The value of n is: " << n << '\n';
 	std::cout << "The value of o is: " << o << '\n';

	if ((k == l && m == n) && (k == m && o == k)) {
        std::cout << "They all have the same value!" << '\n';
  	}

	// You can also initialize using strings!
 	mpz_class p("123456789101112131415161718192021222324252627282930");
 	std::cout << "The value of p is: " << p;
    
	return 0;	
}
```
Now we need to compile our code. I am using g++ but the process will be similar for the compiler of your choice. The only additional thing we have to do is link the GMP libgmp and libgmpxx libraries using the -l flag.
```
g++ test1.cpp -lgmp -lgmpxx
```
Then run the executable and the output will look something like this:
```
The value of k is: 37200000000000
The value of l is: 37200000000000
The value of m is: 37200000000000
The value of n is: 37200000000000
The value of o is: 37200000000000
They all have the same value!
The value of p is: 123456789101112131415161718192021222324252627282930
```
Be careful when creating the mpz_class object, since initialization with the parentheses, curly braces or the standard '=' sign essentially converts an int type to mpz_class. This may result in overflowing if the number is too large to fit in a standard type (which probably will be the case since this is why we are using the library in the first place). If you want to give an initial value that can't fit in a standard type then use the string method.

Also notice that in order to pass the integer to the cout stream we didn't have to use a specific function; instead, we simply used the standard insertion operator '<<'. The C++ library has overloaded operators which allow us to use mpz_class objects just as we would use a standard integer. We can showcase this in the following program:
```
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
```
Remember to link the source code with the lgmp and lgmpxx libraries! The console will print:
```
a is: 1500000000000000000000 while b is: 150000000000000000000
The value of a + b is: 1650000000000000000000
The value of a - b is: 1350000000000000000000
The value of a * b is: 225000000000000000000000000000000000000000
The value of a / b is: 10
The value of a % b is: 0
The value of -a is: -1500000000000000000000
d is a mpz_class, e is an int; d + e = 44
d is a mpz_class, l is a double; d + l = 13
d is a mpz_class, m is a long long, so they can't be directly added; using conversion d + m = 12
> works as intended
>= works too
Comparisons with standard types work!
```

As you can see, intermixing with most of the standard types works perfectly. Unfortunately, the long long, long double and bool types are not accepted directly, but must be explicitly cast to another type first (as I did with m).

GMP includes a lot of very useful functions. The most important of them have equivalents for the C++ classes (like absolute valye, greatest common denominator, or factorial), while others work only for the C GMP types. You can easily utilize them with the C++ types by passing a reference of the underlying C object with the functions:

For mpz: mpz_t mpz_class::get_mpz_t()
For mpq: mpq_t mpq_class::get_mpq_t()
For mpf: mpf_t mpf_class::get_mpf_t()

The following program showcases some of the functions included:
```
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
```
The output is:
```
A is: 300 while B is: 360
The greatest common divisor of A and B is: 60
The absolute value of -A (-300) is: 300
C is: 2
C raised to the power of 100 is: 1267650600228229401496703205376
```
As a final example, I'll use an insertion sort algorirthm with templates I have created in order to sort a mpz_class array. I'll read and insert the values to the array with strings.
```
#include <iostream>
#include <gmpxx.h>

template <typename T>
void insertion_sort(T arr[], int N)
{
    for (int i = 1; i < N; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j-1]) {
                auto temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
            else break;
        }
    }
    return;
}

int main() 
{
    int size;
    std::cin >> size;
    std::cin.ignore(100, '\n'); // tell the input to ignore the first newline character
    mpz_class arr[size];
    std::string in;

    // read the numbers line by line
    for (int i = 0; i < size; i++) {
        std::getline(std::cin, in);
        arr[i] = in;
    }

    std::cout << "Array before sorting: " << '\n';
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << '\n';
    }

    insertion_sort(arr, size);
    std::cout << "Array after sorting: " << '\n';
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << '\n';
    }

    return 0;
}
```
If I give the console the following input:
```
10
99999999999999999999999999999999999999999999999999
88888888888888888888888888888888888888888888888888
77777777777777777777777777777777777777777777777777
66666666666666666666666666666666666666666666666666
55555555555555555555555555555555555555555555555555
44444444444444444444444444444444444444444444444444
33333333333333333333333333333333333333333333333333
22222222222222222222222222222222222222222222222222
11111111111111111111111111111111111111111111111111
00000000000000000000000000000000000000000000000000
```
Then the output would be:
```
Array before sorting: 
99999999999999999999999999999999999999999999999999
88888888888888888888888888888888888888888888888888
77777777777777777777777777777777777777777777777777
66666666666666666666666666666666666666666666666666
55555555555555555555555555555555555555555555555555
44444444444444444444444444444444444444444444444444
33333333333333333333333333333333333333333333333333
22222222222222222222222222222222222222222222222222
11111111111111111111111111111111111111111111111111
0
Array after sorting: 
0
11111111111111111111111111111111111111111111111111
22222222222222222222222222222222222222222222222222
33333333333333333333333333333333333333333333333333
44444444444444444444444444444444444444444444444444
55555555555555555555555555555555555555555555555555
66666666666666666666666666666666666666666666666666
77777777777777777777777777777777777777777777777777
88888888888888888888888888888888888888888888888888
99999999999999999999999999999999999999999999999999

```
I would like to note here that in the insertion_sort function I used auto to declare the temp variable. However, due to possible crashes when combining auto with the mpz_class in certain occasions, it is recommended to avoid auto anywhere a GMP C++ expression may appear. Finally, notice that a string of 50 zeros is automatically converted to 0.

I have added all of the above programs to the Example folder in the repository.

## Useful links

GMP main page: https://gmplib.org/

GMP documentation in PDF format: https://gmplib.org/gmp-man-6.2.0.pdf

Manual of the C++ interface, main section: https://gmplib.org/manual/C_002b_002b-Interface-General.html

Manual of the C++ interface, integers section: https://gmplib.org/manual/C_002b_002b-Interface-Integers.html#C_002b_002b-Interface-Integers
