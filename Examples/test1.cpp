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
