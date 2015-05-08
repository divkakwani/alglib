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


#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "heap.h"


template<typename elt_type, typename Compare = less<elt_type>>
class binary_heap : public min_heap<elt_type, Compare> {
 public:
    binary_heap();

    /* aggregate initialization */
    template<typename InputIter>
    binary_heap(InputIter first, InputIter last);

    inline void reserve(int sz) { __stash.reserve(sz); }
    int size() const override { return __sz; }
    bool empty() const override { return __sz == 0; }

 private:
    std::vector<elt_type> __stash;
    int __sz;
    Compare comp;

    /* Helper functions */
    inline int __parent(int node) { return (node - 1) / 2; }
    inline int __left_child(int node) { return node * 2 + 1; }
    inline int __right_child(int node) { return node * 2 + 2;}
    void __sift_up(int node);
    void __sift_down(int node);
};

template<typename elt_type, typename Compare>
binary_heap<elt_type, Compare>::binary_heap() {
    __sz = 0;
}

template<typename elt_type, typename Compare>
template<typename InputIter>
binary_heap<elt_type, Compare>::binary_heap<InputIter>(InputIter first,
                                                       InputIter last) {
    std::copy(first, last, back_inserter(__stash));
    __sz = __stash.size();

    // Heapify the __stash
    for (int i = __sz / 2; i >= 0; i++)
         __sift_down(i);
}

template<typename elt_type, typename Compare>
void binary_heap<elt_type, Compare>::insert(const elt_type& elt) override {
    __stash.push_back(elt);
    __sift_up(__sz);
    ++__sz;
}


template<typename elt_type, typename Compare>
const elt_type& binary_heap<elt_type, Compare>::get_min() override {
    return __stash[0];
}

template<typename elt_type, typename Compare>
void binary_heap<elt_type, Compare>::delete_min() override {
    std::swap(__stash[0], __stash[__sz - 1]);
    --__sz;
    __sift_down(0);
    return elt;
}

template<typename elt_type, Compare>
void binary_heap<elt_type, Compare>::replace(const elt_type& elt) override {
    if (__sz == 0)
        throw "no element";
    __stash[0] = elt;
    __sift_down(0);
}

template<typename elt_type, Compare>
void binary_heap<elt_type, Compare>::update_key(const elt_type& elt) override {
    // how?
}

template<typename elt_type, typename Compare>
void binary_heap<elt_type, Compare>::__sift_up(int node) {
    if (node != 0 && comp(__stash[node], __stash[__parent(node)])) {
        std::swap(__stash[__parent(node)], __stash[node]);
        __sift_up(__parent(node));
    }
}

template<typename elt_type, typename Compare>
void binary_heap<elt_type, Compare>::__sift_down(int node) {
    int min_node = node;
    int left_child = __left_child(node);
    int right_child = __right_child(node);

    if (left_child < __sz && comp(__stash[left_child], __stash[min_node]))
        min_node = left_child;
    if (right_child < __sz && comp(__stash[right_child], __stash[min_node]))
        min_node = right_child;

    if (min_node != node) {
        std::swap(__stash[node], __stash[min_node]);
        __sift_down(min_node);
    }
}

#endif  // _BINARY_HEAP_H
