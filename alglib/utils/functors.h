/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


#pragma once

#include <bits/stdc++.h>

/* This header files contains definitions of several useful generalized functor types.
 *
 * Some types are implemented through std::function. These types use type erasure to 
 * generalize functors(see the implementation of std::function). Consequently, a call 
 * to such a functor involves dynamic dispatch which increases the run-time.
 */

// A Binary Predicate
template<typename T1, typename T2>
using binary_predicate = std::function<bool (const T1&, const T2&)>;


// A Unary Predicate
template<typename T>
using unary_predicate = std::function<bool (const T&)>;




