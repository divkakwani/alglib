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
#include <cstdlib>
#include "../containers/binary_heap.h"

// The default comparsion functor for sorting functions.
// This just calls operator< as defined by the type T.
template<typename T>
struct DefaultLT {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

template<typename ForwardIter, typename BinaryPred>
void selection_sort(ForwardIter first, ForwardIter last, const BinaryPred& LT) {
    for (auto it = first; it != last; it++)
        std::swap(*it, *std::min_element(it, last, LT));

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


template<typename ForwardIter>
inline void selection_sort(ForwardIter first, ForwardIter last) {
    selection_sort(first, last, DefaultLT<typename ForwardIter::value_type>());
}


// Quick sort helper function
template<typename RandomAccessIter, typename BinaryPred>
RandomAccessIter randomized_partition(RandomAccessIter first,
                                      RandomAccessIter last,
                                      const BinaryPred& LT) {
    /* The function selects a random element in [first, last) as pivot and
     * partitions the interval around it.
     * The part
     */
    int sz = std::distance(first, last);

    RandomAccessIter it = first + rand() % sz;  // O(n) cost
    std::swap(*it, *(last - 1));
    auto pivot = last - 1;

    RandomAccessIter sep = first;  // sep heads the larger-elements partition
    for (auto it = first; it != last; it++) {
        if (*it < *pivot) {
            std::swap(*it, *sep);
            sep++;
        }
    }
    std::swap(*pivot, *sep);
    return sep;
}

template<typename RandomAccessIter, typename BinaryPred>
void quick_sort(RandomAccessIter first, RandomAccessIter last,
                const BinaryPred& LT) {
    if (first < last) {
        RandomAccessIter pivot = randomized_partition(first, last, LT);
        quick_sort(first, pivot, LT);
        quick_sort(pivot + 1, last, LT);
    }
}


template<typename RandomAccessIter>
void quick_sort(RandomAccessIter first, RandomAccessIter last) {
    quick_sort(first, last, DefaultLT<typename RandomAccessIter::value_type>());
}


template<typename RandomAccessIter, typename BinaryPred>
void merge_sort(RandomAccessIter first, RandomAccessIter last,
                const BinaryPred& LT) {
    int sz = std::distance(first, last);
    if (sz > 1) {
        std::vector<typename RandomAccessIter::value_type>
            subarr1(first, first + sz / 2);
        std::vector<typename RandomAccessIter::value_type>
            subarr2(first + sz / 2, last);
        merge_sort(subarr1.begin(), subarr1.end(), LT);
        merge_sort(subarr2.begin(), subarr2.end(), LT);
        std::merge(subarr1.begin(), subarr1.end(),
                   subarr2.begin(), subarr2.end(), first);
    }
}

template<typename RandomAccessIter>
void merge_sort(RandomAccessIter first, RandomAccessIter last) {
    merge_sort(first, last, DefaultLT<typename RandomAccessIter::value_type>());
}


template<typename RandomAccessIter, typename BinaryPred>
void heap_sort(RandomAccessIter first, RandomAccessIter last,
               const BinaryPred& LT) {
    typedef
    typename std::iterator_traits<RandomAccessIter>::value_type val_type;

    binary_heap<val_type> H;  // Use LT here

    for (RandomAccessIter it = first; it != last; it++)
        H.insert(*it);

    for (RandomAccessIter it = first; it != last; it++)
        *it = H.extract_min();
}


template<typename RandomAccessIter>
void heap_sort(RandomAccessIter first, RandomAccessIter last) {
    heap_sort(first, last, DefaultLT<typename RandomAccessIter::value_type>());
}





#endif  // _ALGLIB_SORT_H_
