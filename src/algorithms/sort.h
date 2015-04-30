/************
Copyright 2015 Divyanshu Kakwani
This library contains a collection of sorting algorithms, all of which can be applied on STL containers.
The functions are templatized by the iterator type. A sorting function in general has the following interface:
		<sorting_algorithm>(BEGIN_ITERATOR, END_ITERATOR, GREATER functor);

Author : Divyanshu Kakwani
Sorting Algorithms :
	Comparsion Sorting Algorithms
		Bubble Sort, Insertion sort, Selection sort, Merge sort, Quicksort, Shell sort, Heap sort
Compatibility : C++11 onwards

***************/



#ifndef _ALGLIB_SORT_H_
#define _ALGLIB_SORT_H_

#include <vector>
#include <algorithm>
#include <iterator>
#include "../containers/binary_heap.h"

template<typename ForwardIter>
void selection_sort(ForwardIter first, ForwardIter last) {
    for (auto it = first; it != last; it++)
        std::swap(*it, *std::min_element(it, last));

    /* Analysis
     *   Proof of Correctness:
     *     We prove it using the following invariant:
     *       Prior to an iteration of the loop, A[first..it-1] contains
     *       the smallest (it-first) elements of A in a non-decreasing order.
     *     Initialization: Initially, it = first, so A[first..first-1] contains
     *     no element. Hence it is trivially sorted.
     *     Maintenance: A[first..it-1] is sorted prior to an iteration, and in
     *     the loop A[it] is set to a minimum element in A[it..last].
     *     A[it] >= E, E ϵ A[first..it-1] because prior to the iteration,
     *     A[it..last] did not contain any element greater than E,
     *     E ϵ A[first..it-1]. Hence, A[first..it] contains its elements in a
     *     non-decreasing order. Further, the range also contains the smallest
     *     (it-first+1) elemnts of A since one more is added in the loop.
     *     Termination: At the end, we have, A[first..last] contains all the
     *     the elemets in a non-decreasing order. This proves the claim.
     *
     *  Stable: Yes (Depends on the implementation of min_element. If it
     *          returns the first minimum element, then it is stable.)
     *  In-place: Yes
     *  Time-Complexity Gurantee: O(n^2).
     *  The loop runs n times and each of the iteration invoke min_element,
     *  which takes O(i) time where i goes from 1 to n.
     *  Mutual-Exclusion: required.
     */
}

template<typename ForwardIter, typename BinaryFunct>
void selection_sort(ForwardIter first, ForwardIter last, BinaryFunct LT) {
    for (auto it = first; it != last; it++)
        std::swap(*it, *std::min_element(it, last, LT));
}


// Quick sort helper function
template<typename _RandomAccessIter>
_RandomAccessIter randomized_partition(_RandomAccessIter _first,
                                       _RandomAccessIter _last) {
    _RandomAccessIter it = _first + rand_r() % (_last - _first);  // O(n) cost
    _RandomAccessIter pivot = _last - 1;
    std::swap(*pivot, *it);
    _RandomAccessIter sep = _first;  // sep heads the larger-elements partition
    for (it = _first; it != _last; it++) {
        if (*it < *pivot) {
            std::swap(*it, *sep);
            sep++;
        }
    }
    std::swap(*pivot, *sep);
    return sep;
}

template<typename _RandomAccessIter>
void quick_sort(_RandomAccessIter _first, _RandomAccessIter _last) {
    if (_first < _last) {
        _RandomAccessIter pivot = randomized_partition(_first, _last);
        quick_sort(_first, pivot);
        quick_sort(pivot + 1, _last);
    }
}



template<typename RandomAccessIter>
void merge_sort(RandomAccessIter _first, RandomAccessIter _last) {
    int sz = _last - _first;
    if (sz > 1) {
        std::vector<typename RandomAccessIter::value_type>
            subarr1(_first, _first + sz / 2);
        std::vector<typename RandomAccessIter::value_type>
            subarr2(_first + sz / 2, _last);
        merge_sort(subarr1.begin(), subarr1.end());
        merge_sort(subarr2.begin(), subarr2.end());
        std::merge(subarr1.begin(), subarr1.end(),
                   subarr2.begin(), subarr2.end(), _first);
    }
}





template<typename RandomAccessIter>
void heap_sort(RandomAccessIter first, RandomAccessIter last) {
    typedef
    typename std::iterator_traits<RandomAccessIter>::value_type val_type;

    binary_heap<val_type> H;

    for (RandomAccessIter it = first; it != last; it++)
        H.insert(*it);

    for (RandomAccessIter it = first; it != last; it++)
        *it = H.extract_min();
}





#endif  // _ALGLIB_SORT_H_
