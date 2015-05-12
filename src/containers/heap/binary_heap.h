/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef _BINARY_HEAP_H
#define _BINARY_HEAP_H

#include <boost/concept_check.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "heap.h"

// TODO(divkakwani): Convert to rvalue-references



template<typename elt_t, typename key_t>
class binary_heap : public min_heap<elt_t, key_t> {
    BOOST_CONCEPT_ASSERT((boost::LessThanComparable<elt_t>));
    BOOST_CONCEPT_ASSERT((boost::LessThanComparable<key_t>));

 public:
    /* typedefs */
    typedef elt_t elt_type;
    typedef key_t key_type;

    /* Default Ctor */
    binary_heap();

    /* aggregate initialization */
    template<typename InputIter>
    binary_heap(InputIter elt_first, InputIter elt_last, InputIter key_first);


    void insert(const elt_t& elt, const key_t& key);

    /* get the root */
    const elt_t& get_min_elt() const;
    const key_t& get_min_key() const;

    /* remove the root */
    void delete_min();
    void replace(const elt_t& elt, const key_t& key);

    /* Inspection */
    int size() const override { return __sz; }
    bool empty() const override { return __sz == 0; }

    /* Internal modification */
    void update_key(const elt_t& elt, const key_t& key);


 private:
    /* `node` is wrapper around the key with an additional pointer to
     * the element which it is associated with.
     */
    struct node_t {
        key_t key;
        typename std::map<elt_t, int>::iterator elt_it;
        bool operator<(const node_t& other) const { return key < other.key; }
    };

    /* `nodeof` stores the node corresponding to element inserted in the heap.
     * The heap only contains the nodes. To go from an element to its
     * node or from a node back to its element, we'll have to go through
     * `nodeof`
     */
    std::map<elt_t, int> nodeof;

    /* The heap is stored in this array */
    std::vector<node_t> heaparr;
    int __sz;

    typename std::map<elt_t, int>::iterator make_entry(const elt_t& elt) {
        if (nodeof.find(elt) != nodeof.end())
            throw "Element already exists";
        nodeof[elt] = -1;
        return nodeof.find(elt);
    }
    void update_entry(int idx) { (heaparr[idx].elt_it)->second = idx; }

    /* Helper functions */
    inline int __parent(int node) { return (node - 1) / 2; }
    inline int __left_child(int node) { return node * 2 + 1; }
    inline int __right_child(int node) { return node * 2 + 2; }
    void __sift_up(int node);
    void __sift_down(int node);
};

template<typename elt_t, typename key_t>
binary_heap<elt_t, key_t>::binary_heap() {
    __sz = 0;
}

template<typename elt_t, typename key_t>
template<typename InputIter>
binary_heap<elt_t, key_t>::binary_heap(InputIter elt_first,
                                       InputIter elt_last,
                                       InputIter key_first) {
    __sz = 0;
    while (elt_first != elt_last) {
        auto loc = make_entry(*elt_first);
        heaparr[__sz++] = node_t {*key_first, loc};
        ++elt_first;
    }

    // Heapify the __stash
    for (int i = __sz / 2; i >= 0; i--)
         __sift_down(i);
}

template<typename elt_t, typename key_t>
void binary_heap<elt_t, key_t>::insert(const elt_t& elt,
                                       const key_t& key) {
    auto loc = make_entry(elt);
    heaparr.push_back(node_t {key, loc});
    __sift_up(__sz);
    ++__sz;
}


template<typename elt_t, typename key_t>
const elt_t& binary_heap<elt_t, key_t>::get_min_elt() const {
    return (heaparr[0].elt_it)->first;
}


template<typename elt_t, typename key_t>
const key_t& binary_heap<elt_t, key_t>::get_min_key() const {
    return heaparr[0].key;
}

template<typename elt_t, typename key_t>
void binary_heap<elt_t, key_t>::delete_min() {
    nodeof.erase(heaparr[0].elt_it);
    std::swap(heaparr[0], heaparr[__sz - 1]);
    --__sz;
    __sift_down(0);
}

template<typename elt_t, typename key_t>
void binary_heap<elt_t, key_t>::replace(const elt_t& elt,
                                        const key_t& key) {
    if (__sz == 0)
        throw "no element";
    auto loc = make_entry(elt);
    nodeof.erase(heaparr[0].elt_it);  // Clean up the elt from nodeof map
    heaparr[0] = node_t {key, loc};
    __sift_down(0);
}

template<typename elt_t, typename key_t>
void binary_heap<elt_t, key_t>::update_key(const elt_t& elt,
                                           const key_t& key) {
    if (nodeof.find(elt) == nodeof.end())
        throw "Non-existent element";
    int index_in_heap = nodeof[elt];
    heaparr[index_in_heap] = node_t {key, heaparr[index_in_heap].elt_it};
    __sift_up(index_in_heap);
    __sift_down(index_in_heap);
}

template<typename elt_t, typename key_t>
void binary_heap<elt_t, key_t>::__sift_up(int node) {
    /*
     * Store the node in a temp and move all the other nodes encountered
     * while going upwards down and finally put the temp in the upmost place.
     */
    node_t temp = heaparr[node];
    while (node != 0 && temp < heaparr[__parent(node)]) {
        heaparr[node] = heaparr[__parent(node)];
        update_entry(node);
        node = __parent(node);
    }
    heaparr[node] = temp;
    update_entry(node);
}

template<typename elt_t, typename key_t>
void binary_heap<elt_t, key_t>::__sift_down(int node) {
    int min_node = node;
    int left_child = __left_child(node);
    int right_child = __right_child(node);

    if (left_child < __sz && heaparr[left_child] < heaparr[min_node])
        min_node = left_child;
    if (right_child < __sz && heaparr[right_child] < heaparr[min_node])
        min_node = right_child;

    if (min_node != node) {
        std::swap(heaparr[node], heaparr[min_node]);
        update_entry(node);
        update_entry(min_node);
        __sift_down(min_node);
    }
}

/* Partial specialization of the heap class for the case when the prioritizing
 * order is the natural order itself.
 */
template<typename elt_t>
class unkeyed_binary_heap {
 private:
    binary_heap<elt_t, elt_t> heap;

 public:
    void insert(const elt_t& elt) { heap.insert(elt, elt); }

    /* get the root */
    const elt_t& get_min() const { return heap.get_min_elt(); }

    /* remove the root */
    void delete_min() { heap.delete_min(); }
    void replace(const elt_t& elt) { heap.replace(elt, elt); }

    /* Inspection */
    int size() const { return heap.size(); }
    bool empty() const { return heap.empty(); }
};



#endif  // _BINARY_HEAP_H
