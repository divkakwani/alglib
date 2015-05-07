#include <iostream>
#include "heap.h"
#include <vector>
#include <algorithm>

// binary_heap interface
// 	1. insert
//	2. extract_min/ extract_max
//	3. create_heap
//	4. 

template<typename elt_type>
class binary_heap : min_heap<elt_type> {

		std::vector<elt_type> __stash;
		int __sz;
		
		/** Helper functions */
		inline int __parent(int node);
		inline int __left_child(int node);
		inline int __right_child(int node);
		void __bubble_up(int node);
		void __bubble_down(int node);
		
	public:
		binary_heap(int sz = 0);
		// add a ctor for initialization through an array.
		void insert(elt_type elt);
		elt_type extract_min();		
};

template<typename elt_type>
binary_heap<elt_type>::binary_heap(int sz) {
	__sz = sz;
	__stash.reserve(sz);
	
}

template<typename elt_type>
void binary_heap<elt_type>::insert(elt_type elt) {

	__stash.push_back(elt);
	__bubble_up(__sz);
	++__sz;
}

template<typename elt_type>
elt_type binary_heap<elt_type>::extract_min() {
	
	elt_type elt = __stash[0];
	std::swap(__stash[0], __stash[__sz - 1]);	// FIXME : handle the dtor
	--__sz;
	__bubble_down(0);
	return elt;
}

template<typename elt_type>
void binary_heap<elt_type>::__bubble_up(int node) {
	int parent = __parent(node);
	while(parent >= 0 and __stash[parent] > __stash[node]) {
		std::swap(__stash[parent], __stash[node]);
		node = parent;
		parent = __parent(node);
	}

}

template<typename elt_type>
void binary_heap<elt_type>::__bubble_down(int node) {
	int min_idx = node;
	int left_idx = __left_child(node);
	int right_idx = __right_child(node);
	
	if(left_idx < __sz and __stash[left_idx] < __stash[min_idx])
		min_idx = left_idx;
	if(right_idx < __sz and __stash[right_idx] < __stash[min_idx])
		min_idx = right_idx;
	
	if(min_idx != node) {
		std::swap(__stash[node], __stash[min_idx]);
		__bubble_down(min_idx);
	}
}

template<typename elt_type>
inline int binary_heap<elt_type>::__parent(int node) {
	return node / 2;
}

template<typename elt_type>
inline int binary_heap<elt_type>::__left_child(int node) {
	return 2 * node + 1;
}

template<typename elt_type>
inline int binary_heap<elt_type>::__right_child(int node) {
	return 2 * node + 2;
}




