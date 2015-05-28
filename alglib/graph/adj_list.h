/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#include <iostream>
#include <map>
#include <boost/iterator/transform_iterator.hpp>
#include <alglib/graph/graph_model.h>

#pragma once

/**
 * \breif A functor that returns the first element of a pair
 *
 */
template<typename T>
struct get_first {
    const typename T::first_type& operator() (const T& p) const { return p.first; }
};

/**
 * \breif A functor that returns the second element of a pair
 *
 */
template<typename T>
struct get_second {
    const typename T::second_type& operator() (const T& p) const { return p.second; }
};


/**
 * \breif A 'model' of a graph
 *
 */

template<typename vertex_t, typename edge_t>
class adj_list : public graph_model<vertex_t, edge_t> {

 public:
    
    /// Returs true if the two given vertices are adjacent, otherwise false
    bool are_adj (const vertex_t&, const vertex_t&) const;

    void add_vertex (const vertex_t& v);
    void add_edge (const vertex_t& u, const vertex_t& v, const edge_t& a);
    void add_edge (const edge_t& e);
    void remove_vertex (const vertex_t& v);
    void remove_edge (const vertex_t& u, const vertex_t& v);
        
    int indeg (const vertex_t& v) const;
    int outdeg (const vertex_t& v) const;

    int num_vertices () const;
    int num_edges () const;
    
 

    typedef std::map<vertex_t, edge_t> alist_t; 
    
    /// Iterators
    typedef boost::transform_iterator<get_first<std::pair<vertex_t, alist_t>>,
                                      typename std::map<vertex_t, alist_t>::iterator>
            const_viterator;

    typedef boost::transform_iterator<get_first<std::pair<vertex_t, edge_t>>,
                                      typename std::map<vertex_t, edge_t>::iterator>
            const_aviterator;
    typedef boost::transform_iterator<get_second<std::pair<vertex_t, edge_t>>,
                                      typename std::map<vertex_t, edge_t>::iterator>
            const_aeiterator;
    
    class const_eiterator;
    
    /// Returns an iterator to the beg
    const_viterator vbegin();
    const_viterator vend();
    const_eiterator ebegin();
    const_eiterator eend();
    const_aviterator avbegin(const vertex_t& v);
    const_aviterator avend(const vertex_t& v);
    const_aeiterator aebegin(const vertex_t& v);
    const_aeiterator aeend(const vertex_t& v);


 private:
       
    std::map<vertex_t, alist_t>   alists;
    
};


template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::add_vertex(const vertex_t& v) {
    /**
     *  If the vertex doesn't already exist, create a new entry in alists
     *  and initialize it with an empty alist.
     *  Complexity: O(lg n)
     */
    if(alists.find(v) == alists.end())
        alists[v] = alist_t();

}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::add_edge(const vertex_t& u,
                                                 const vertex_t& v,
                                                 const edge_t& e) {
    /**
     *  Add vertex u and v if they don't already exist. Then insert e into
     *  the adjacency list of u.
     *  Complexity Gurantee: O(lg n)
     */
    
    add_vertex(u);
    add_vertex(v);
    
    alists[u][v] = e;
}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::add_edge(const edge_t& e) {
    /**
     *  Ensure that both e.from and e.to exist and then insert e into
     *  the adjacency list of e.from.
     *  Complexity Gurantee: O(lg n)
     */
    add_vertex(e.from);
    add_vertex(e.to);
    
    alists[e.from][e.to] = e;
}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::remove_vertex(const vertex_t& v){
     /**
      *  Delete the adjacency list of v. Then, delete v from any other alist
      *  that contains it.
      *  Complexity Gurantee: O(V lg V)
      */

    alists.erase(v);
    
    for(auto& entry : alists) {
        entry.second.erase(v);
    }
}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::remove_edge(const vertex_t& u,
                                                    const vertex_t& v) {
    /**
     *  Remove v from the adjacency list of u.
     *  Complexity Gurantee: O(lg outdeg u)
     */
    alists[u].erase(v);
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::indeg(const vertex_t& v) const {
    /**
     *  For each alist, if v exists in the alist, increment deg by 1.
     *  Complexity Gurantee: O(V lg V)
     */

    int deg = 0;

    for(auto& entry : alists) {
        auto& alist = entry.second;
        if(alist.find(v) != alist.end())
            deg++
    }
    return deg;
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::outdeg(const vertex_t& v) const {
    /**
     *  Locate the alist of v and return its size.
     *  Complexity Gurantee: O(lg V)
     */
    return alists.at(v).size();
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::num_vertices() const {
    /**
     *  Complexity Gurantee: O(1)
     */

    return alists.size();
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::num_edges() const {
    /**
     *  Sum the sizes of all the alists.
     *  Complexity Gurantee: O(V lg V)
     */

    int sum = 0;    
    for(auto& entry : alists)
        sum += entry.second.size();
    return sum;
}


template<typename vertex_t, typename edge_t>
inline bool adj_list<vertex_t, edge_t>::are_adj(const vertex_t& u,
                                                const vertex_t& v) const {
    /** 
     *  If v exists in the adjacency list of u, then return true, otherwise
     *  false.
     *  Complexity Gurantee: O(lg V + lg deg u)
     */
    
    return alists.at(u).find(v) != alists.at(u).end();
}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_viterator
adj_list<vertex_t, edge_t>::vbegin() {
    /**
     *  Using boost::transform_iterator, transform the map iterator to
     *  look like an iterator to a sequential container holding vertices.
     *  Complexity Gurantee: O(1)
     */
    get_first<std::pair<vertex_t, alist_t>> trans;
    return boost::make_transform_iterator(alists.begin(), trans);
}
    
template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_viterator 
adj_list<vertex_t, edge_t>::vend() {
    /**
     *  Complexity Gurantee: O(1)
     */
    get_first<std::pair<vertex_t, alist_t>> trans;
    return boost::make_transform_iterator(alists.end(), trans);
}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aviterator 
adj_list<vertex_t, edge_t>::avbegin(const vertex_t& u) {
    /**
     *  Complexity Gurantee: O(lg V)
     */
    get_first<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].begin(), trans);
}



template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aviterator 
adj_list<vertex_t, edge_t>::avend(const vertex_t& u) { 
    /**
     *  Complexity Gurantee: O(lg V)
     */

    get_first<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].end(), trans);
}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aeiterator 
adj_list<vertex_t, edge_t>::aebegin(const vertex_t& u) {
    /** 
     *  Complexity Gurantee: O(lg V)
     */
    get_second<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].begin(), trans);
}



template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aeiterator
adj_list<vertex_t, edge_t>::aeend(const vertex_t& u) { 
    /** 
     *  Complexity Gurantee: O(lg V)
     */
    get_second<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].end(), trans);
}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_eiterator 
adj_list<vertex_t, edge_t>::ebegin() {
    /**
     *  Complexity Gurantee: O(1)
     */
    return const_eiterator(*this);
}



template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_eiterator 
adj_list<vertex_t, edge_t>::eend() { 
    /**
     *  Complexity Gurantee: O(1)
     */
    const_eiterator it(*this);
    it.vit = vend();
    return it;
}


template<typename vertex_t, typename edge_t>
class adj_list<vertex_t, edge_t>::const_eiterator {

 private:
    const_aeiterator aeit;
    const_viterator  vit;
    adj_list<vertex_t, edge_t>& object;

    friend class adj_list<vertex_t, edge_t>;

    template<typename t1, typename t2>
    friend std::ostream& operator<<(std::ostream& out, typename adj_list<t1, t2>::const_eiterator cit);

    const_eiterator() { }

 public:
    

    const_eiterator(adj_list<vertex_t, edge_t>& obj) : object(obj) {
        if(object.alists.size() != 0) {
            vit = obj.vbegin();
            aeit = obj.aebegin(*vit);
        }
    }

    const_eiterator(const const_eiterator& eit) : object(eit.object){
        vit = eit.vit;
        aeit = eit.aeit;

    }


    void operator++() {
        aeit++;
        if(aeit == object.aeend(*vit)) {
            vit++;
            while(vit != object.vend() and object.aebegin(*vit) == object.aeend(*vit))
                vit++;
            aeit = object.aebegin(*vit);
        }
        //return *aeit;  // FIXME: set to previos aeit;
    }

    const edge_t& operator*() {

        return *aeit;
    }

    bool operator==(const const_eiterator& other) const {
        return (vit == other.vit && aeit == other.aeit) || (vit == other.vit && vit == object.vend());
    } 

    bool operator!=(const const_eiterator& other) const {
        return !(*this == other);
    }

};


template<typename vertex_t, typename edge_t>
std::ostream& operator<<(std::ostream& out, typename adj_list<vertex_t, edge_t>::const_eiterator eit) {
 
        out << *(eit.aeit);
        return out;

}
