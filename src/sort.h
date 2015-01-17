/************
This library contains a collection of sorting algorithms, all of which can be applied on STL containers.
The functions are templatized by the iterator type. A sorting function in general has the following interface:
		<sorting_algorithm>(BEGIN_ITERATOR, END_ITERATOR, GREATER functor);

Author : Divyanshu Kakwani
Sorting Algorithms : 
	Comparsion Sorting Algorithms
		Bubble Sort, Insertion sort, Selection sort, Merge sort, Quicksort, Shell sort, Heap sort
Compatibility : C++11 onwards

***************/



#ifndef __SORT__H
#define __SORT__H

#include <vector>
#include <algorithm>



template<typename _RandomAccessIterator>
void selection_sort(_RandomAccessIterator _first, _RandomAccessIterator _last) {
	for(auto it = _first; it != _last; it++)
		std::swap(*it, *std::min_element(it, _last));
}


template<typename _RandomAccessIterator>
void quick_sort(_RandomAccessIterator _first, _RandomAccessIterator _last) {
}



#endif
