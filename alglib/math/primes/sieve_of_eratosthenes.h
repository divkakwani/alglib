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

template<typename T>
struct increment {
    T operator() (T n) { return ++n; }
};

template<
          long long MaxNum,
          long long Start = 2,
          long long End = sqrt(MaxNum),
          typename UnaryFunc = increment<long long>
        >
class eratosthenes_sieve {

 private:
     int sieve[max_num + 1];
     const long long max_num;
     const long long start;
     const long long end;

 public:


    eratosthenes_sieve() : max_num(MaxNum), start(Start), end(End) {

        fill(sieve, sieve + max_number + 1, 0);

        for(long long no = start; no <= end; no++) 
            for(long long multiple = 2 * no; multiple <= max_number; multiple += no)
                sieve[multiple] = update(sieve[multiple]);
    }

    int get_ith_val(long long i) {
        return sieve[i];
    }
};


template<typename OutputIter>
OutputIter get_first_n_primes(long long i, OutputIter dest) {


}

template<typename OutputIter>
OutputIter get_primes_till(long long till, OutputIter dest) {

    eratosthenes_sieve<till> sieve;

    for(int i = 2; i <= till; i++)
        if(get_ith_val(i) == 0)
            *dest++ = i;

    return dest;
}

/*
template<
         long long till,
         long long method = eratosthenes_sieve
        >
class primes;

*/


}  // end of primes namespace
}  // end of math namespace
}  // end of alglib namespace
