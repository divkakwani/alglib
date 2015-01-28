
#ifndef _PARALLEL_SORT_H
#define _PARALLEL_SORT_H

#include <algorithm>
#include <thread>
#include <vector>


template<typename RandomAccessIter>
void merge_sort(RandomAccessIter _first, RandomAccessIter _last) {
	int sz = _last - _first;
	if(sz > 1) {

		// Left subarray
		std::vector<typename RandomAccessIter::value_type> subarr1(_first, _first + sz / 2);
		std::thread left(merge_sort<RandomAccessIter>, subarr1.begin(), subarr1.end());

		// Right subarray
		std::vector<typename RandomAccessIter::value_type> subarr2(_first + sz / 2, _last);
		std::thread right(merge_sort<RandomAccessIter>, subarr2.begin(), subarr2.end());

		left.join();
		right.join();

		std::merge(subarr1.begin(), subarr1.end(), subarr2.begin(), subarr2.end(), _first);
	}
}

#endif
