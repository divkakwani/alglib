
#ifndef _HEAP_H
#define _HEAP_H

// abstract class
// Any heap must conform to this interface

template<typename elt_type>
class min_heap {
	public:
		virtual void insert(elt_type elt) = 0;
		virtual elt_type extract_min() = 0;		// FIXME : should elt_type be returned?
};


#endif
