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



template<typename _RandomAccessIter>
void selection_sort(_RandomAccessIter _first, _RandomAccessIter _last) {
	for(auto it = _first; it != _last; it++)
		std::swap(*it, *std::min_element(it, _last));
}

// Quick sort helper function
template<typename _RandomAccessIter>
_RandomAccessIter randomized_partition(_RandomAccessIter _first, _RandomAccessIter _last) {
	_RandomAccessIter it = _first + rand() % (_last - _first);	// O(n) cost
	_RandomAccessIter pivot = _last - 1;
	std::swap(*pivot, *it);
	_RandomAccessIter sep = _first;	// marks the starting of the larger-elements partition
	for(it = _first; it != _last; it++) {
		if(*it < *pivot) {
			std::swap(*it, *sep);
			sep++;
		}
	}
	std::swap(*pivot, *sep);
	return sep;
}

template<typename _RandomAccessIter>
void quick_sort(_RandomAccessIter _first, _RandomAccessIter _last) {
	if(_first < _last) {
		_RandomAccessIter pivot = randomized_partition(_first, _last);
		quick_sort(_first, pivot);
		quick_sort(pivot + 1, _last);
	}
}



template<typename RandomAccessIter>
void merge_sort(RandomAccessIter _first, RandomAccessIter _last) {
	int sz = _last - _first;
	if(sz > 1) {
		std::vector<int> subarr1, subarr2;
		std::copy(_first, _first + sz / 2, back_inserter(subarr1));
		std::copy(_first + sz / 2, _last, back_inserter(subarr2));
		merge_sort(subarr1.begin(), subarr1.end());
		merge_sort(subarr2.begin(), subarr2.end());
		std::merge(subarr1.begin(), subarr1.end(), subarr2.begin(), subarr2.end(), _first);
	}
}




#endif
