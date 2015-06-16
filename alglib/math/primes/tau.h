/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <vector>
#include <alglib/math/primes/sieve_of_eratosthenes.h>

namespace alglib {
namespace math {
namespace primes {

template<typename num_type, num_type num>
num_type tau() {

    num_type number = num;

    /* Need to find primes only till sqrt(num) - since if it's non-prime, there must be
     * a divisor less than or equal to sqrt(num)
     */
    eratosthenes_sieve<num_type, sqrt(num)> sieve;  

    /* stores just the exponents of the prime divisors of num */
    std::vector<int> exponents;

    for(auto it = sieve.primes_begin(); it != sieve.primes_end() and
                                        number > 1 and (*it) * (*it) <= number; it++) {
        int times = 0;
        while(number % (*it) == 0) {
            times++;
            number /= *it;
        }
        if(times)   exponents.push_back(times); 
    }
    /* If at the end of the above loop, number > 1, then there exists some 
     * prime factor > sqrt(num); Hence, push back 1;
     */
    if(number > 1)   exponents.push_back(1);

    num_type product = 1;
    for(int cnt : exponents) {
        product *= cnt+1;
    }
    return product;
}


}  // end of primes namespace
}  // end of math namespace
}  // end of alglib namespace
