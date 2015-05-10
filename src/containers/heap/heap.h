/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef _HEAP_H
#define _HEAP_H

#include <boost/concept_check.hpp>
#include <functional>

/*
 *  Abstract class for a heap
 *  Any heap must conform to this interface
 *
 *  There are two types of ordering of the type elt_t - natural ordering and
 *  priority ordering. The operator< defines the natural ordering and the
 *  keys associated with the elements define the priority ordering. The former
 *  ordering is defined by the class and the latter by the client of this
 *  library.
 *  The natural ordering is used to establish the equality of two elements. If
 *  none of the two elements is greater than the other, then they are equal.
 *  Hence, the `min_heap` class is configurable with different schemes of
 *  priority ordering by supplying corresponding keys. In case, none is
 *  supplied, the ordering chosen by the `min_heap` defaults to natural
 *  ordering.
 *
 *  The reason of having another variable `key` for ordering the
 *  elements is to decouple the scheme of ordering from the
 *  object itself.
 *  If we use operator< of elt's class, it would be far too
 *  restrictive. It would allow only one type of ordering - the
 *  one defined by the class. In many situations, that may not be
 *  the scheme we require. Worse still, it precludes any non-comparable
 *  item from being used to make a min-heap.
 *  To make this more concrete, consider a use-case in which a shopkeeper
 *  services the requests of his customers. The customers are of Person type
 *  that doesn't have any total-ordering relation. The shopkeeper, however,
 *  can have different schemes of prioritizing his customers, some of them
 *  are -
 *    Prioritize the shop's investor.
 *    Prioritize senior citizens.
 *    Prioritize acquaintances
 *    ... and so on.
 *  The essence of this methodology is that the criterion of ordering should
 *  be specified by the min_heap user, not by the class.
 *
 *  Why not use a functor?
 *  Using a functor can potentially lead to inconsistency of the heap. Since by
 *  allowing the user to supply a user-defined functor, we allow him to change
 *  the priority order arbitrarily and as many times as the user wishes, but
 *  the heap requires that every change be followed by a sift up or a sift down.
 *
 *
 */

template<typename elt_t, typename key_t>
class min_heap {
    BOOST_CONCEPT_ASSERT((LessThanComparable<elt_t>));
    BOOST_CONCEPT_ASSERT((LessThanComparable<key_t>));

 public:
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
    virtual void update_key(const elt_type& elt, const key_t& key) = 0;


    /* return a new heap that is the merger of the heap h and *this. */
    min_heap<elt_t, Compare> merge_heaps(const min_heap<elt_t, Compare>& h);
};


#endif // _HEAP_H
