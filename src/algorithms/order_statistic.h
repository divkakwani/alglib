
#ifndef _ORDER_STATISTIC_H
#define _ORDER_STATISTIC_H

#include "sort.h"

template<typename RandomAccessIter>
RandomAccessIter select_i(RandomAccessIter _first, RandomAccessIter _last, int i) {
	
	if(_last <= _first)
		return _last;
	
	RandomAccessIter pivot = randomized_partition(_first, _last);
	int k = pivot - _first + 1;
	
	if(k == i)
		return pivot;
		
	else if(i < k)
		return select_i(_first, pivot, i);
		
	else
		return select_i(pivot + 1, _last, i - k);
}



#endif
