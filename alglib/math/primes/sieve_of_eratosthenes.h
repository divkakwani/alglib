/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <cmath>
#include <vector>

namespace alglib {
namespace math {
namespace primes {


template<typename num_type, num_type max_num>
class eratosthenes_sieve {

 public:
    typedef num_type number_type;
    typedef typename std::vector<number_type>::const_iterator citer;

 private:
     int sieve[max_num + 1];
     std::vector<number_type> primes;
     number_type sz;  // size of the sieve
     const number_type max_number;

 public:


    eratosthenes_sieve() : max_number(max_num) {

        sz = max_number + 1;  // 1 more than the numbers - because numbers will be directly indexed.
        fill(sieve, sieve + sz, 0);

        number_type sqrt_n = sqrt(max_number);

        /* Need to cross out the multiples of only those numbers that are
         * less than or equal to n, for if a number is composite number, it
         * must have some factor less than sqrt(n).
         */
        for(number_type no = 2; no <= sqrt_n; no++) {
            for(number_type multiple = 2 * no; multiple <= max_number; multiple += no)
                sieve[multiple]++;
        }

        for(number_type no = 2; no < sz; no++) {
            if(!sieve[no])
                primes.push_back(no);
        }

    }

    citer primes_begin() {
        return primes.begin();
    }

    citer primes_end() {
        return primes.end();
    }

    number_type get_ith_prime(number_type i) {
        return primes[i];
    }

};



}  // end of primes namespace
}  // end of math namespace
}  // end of alglib namespace
