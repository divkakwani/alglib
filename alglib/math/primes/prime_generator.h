/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <boost/dynamic_bitset/dynamic_bitset.hpp>


class prime_generator {

 private:
    boost::dynamic_bitset<> sieve;
    long long num;
    
 public:
    prime_generator(long long till) : sieve(till) {
        // Sieving Operation
        for (long long num = 2; num < sqrt(till); num++)
            for (long long multiple = 2 * num; multiple < till; multiple += num)
              sieve.set(multiple);
    }
    void reset() {
        num = 2;
    }
    long long next() {
        while (!sieve.test(++num));
        return num;
    }
};
