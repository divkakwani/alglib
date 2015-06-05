
#ifndef _PARALLEL_SORT_H
#define _PARALLEL_SORT_H

#include <algorithm>
#include <thread>
#include <vector>

namespace alglib {
namespace mutithreaded {

template<typename RandomAccessIter>
void merge_sort(RandomAccessIter first, RandomAccessIter last) {
	int sz = last - first;
	if(sz > 1) {

		// Left subarray - spawn a thread for it
		std::vector<typename RandomAccessIter::value_type> subarr1(first, first + sz / 2);
		std::thread left(merge_sort<RandomAccessIter>, subarr1.begin(), subarr1.end());

		// Right subarray
		std::vector<typename RandomAccessIter::value_type> subarr2(first + sz / 2, last);
		merge_sort<RandomAccessIter>(subarr2.begin(), subarr2.end());

		left.join();

		std::merge(subarr1.begin(), subarr1.end(), subarr2.begin(), subarr2.end(), first);
	}
}

}  // end of multithreaded namespace
}  // end of alglib namespace

#endif
