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
 * Abstract class for a heap
 * Any heap must conform to this interface
 *
 * The class is configurable with different schemes of ordering
 * by supplying corresponding `Compare` functor. It defaults to
 * operator< in case no comparison functor is specified.
 */

template<typename elt_t, typename Compare = less<elt_type>>
class min_heap {
    BOOST_CONCEPT_ASSERT((BinaryPredicate<Compare, elt_t, elt_t>));

 public:
    virtual void insert(const elt_t& elt) = 0;

    /* get the root */
    virtual const elt_t& get_min() const = 0;

    /* remove the root */
    virtual void delete_min() = 0;
    virtual void replace(const elt_type& elt) = 0;

    /* Inspection */
    virtual int size() const = 0;
    virtual bool empty() const = 0;

    /* Internal modification */
    virtual void update_key(const elt_type& elt) = 0;

    /* return a new heap that is the merger of the heap h and *this. */
    min_heap<elt_t, Compare> merge_heaps(const min_heap<elt_t, Compare>& h);
};


#endif // _HEAP_H
