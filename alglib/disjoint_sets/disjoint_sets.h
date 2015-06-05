#include <iostream>
#include <map>
#include <vector>

#pragma once

namespace alglib {
namespace disjoint_sets {


template<typename elt_type>
class disjoint_sets {

 private:
    std::vector<int> parent;

    /* Translate to int */
    std::map<elt_type, int> eltid;
    
    /* Number of elements in the disjoint set */
    int elts;

 public:
    disjoint_sets() : elts(0) {}
    void union_set(const elt_type& e1, const elt_type& e2);
    int find_set(const elt_type& e);
    int find_set_by_id(int id);
    void make_set(const elt_type& e);
    bool same_set(const elt_type& e1, const elt_type& e2);
    int set_count();
    int set_size(const elt_type& e);
};

tempate <typename elt_type>
int disjoint_set<elt_type>::find_set_by_id(int id) {

    if (id == parent[id])
        return id;

    return parent[id] = find_set_by_id(parent[id]);     // Path compression
}

template <typename elt_type>
void disjoint_sets<elt_type>::make_set(const elt_type& e) {

    eltid[e] = elts;
    parent[elts] = elts;
    ++elts; 
}

template <typename elt_type>
int disjoint_sets<elt_type>::find_set(const elt_type& e) {

    return find_set_by_id(eltid[e]);
}

template <typename elt_type>
void disjoint_sets<elt_type>::union_set(const elt_type& e1, const elt_type& e2) {

    int repr_id1 = find_set(e1);
    int repr_id2 = find_set(e2);
    parent[repr_id1] = repr_id2;
}

template <typename elt_type>
bool disjoint_set<elt_type>::same_set(const elt_type& e1, const elt_type& e2) {
    
    return find_set(eltid[e1]) == find_set(eltid[e2]);
}

template <typename elt_type>
int disjoint_set<elt_type>::set_count() {
    
}

template <typename elt_type>
int disjoint_set<elt_type>::set_count() {

}

};  // end disjoint_set namespace
};  // end alglib namespace
