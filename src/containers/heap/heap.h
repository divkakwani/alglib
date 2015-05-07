
#ifndef _HEAP_H
#define _HEAP_H

// abstract class
// Any heap must conform to this interface

/* Why does the min-heap not use operator< for ordering the elements
 * and instead use another variable `key` to order them?
 * 	
 * 	The reason of having another variable `key` for ordering the
 * 	elements is to decouple the scheme of ordering from the 
 * 	object itself.
 * 	If we use operator< of elt's class, it would be far too 
 * 	restrictive. It would allow only one type of ordering - the
 * 	one defined by the class. In many situations, that may not be
 * 	the scheme we require. Worse still, it precludes any non-comparable
 * 	item from being used to make a min-heap.
 *	To make this more concrete, consider a use-case in which a shopkeeper
 *	services the requests of his customers. The customers are of Person type
 *	that doesn't have any total-ordering relation. The shopkeeper, however, 
 *	can have different schemes of prioritizing his customers, some of them
 *	are -
 *		Prioritize the shop's investor.
 *		Prioritize senior citizens.
 *		Prioritize acquaintances
 *		... and so on.
 *	The essence of this methodology is that the criterion of ordering should 
 *	be specified by the min_heap user, not by the class.
 * 
 */


template<typename elt_t, typename key_t>
class min_heap {

	public:

		/* typedefs */
		typedef elt_t elt_type;
		typedef key_t key_type;

		virtual void insert(const elt_t& elt, const key_t& key) = 0;

		/* get the root */
		virtual const elt_t& get_min_elt() const = 0;
		virtual const key_t& get_min_key() const = 0;

		/* remove the root */
		virtual void delete_min() = 0;
		virtual void replace(const elt_type& elt, const key_t& key) = 0;

		/* Inspection */
		virtual int size() const = 0;
		virtual bool empty() const = 0;

		/* Internal modification */	
		virtual void change_key(const elt_type& elt, const key_t& new_key) = 0;

		/* return a new heap that is the merger of the heap h and this. */
		min_heap<elt_t, key_t>& merge_heaps(const min_heap<elt_t, key_t>& h);

};



#endif
