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
    typename T::first_type operator() (const T& p) const { return p.first; }
};

/**
 * \breif A functor that returns the second element of a pair
 *
 */
template<typename T>
struct get_second {
    typename T::second_type operator() (const T& p) const { return p.second; }
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
       
    alist_t                       alist;
    std::map<vertex_t, alist_t>   alists;

    
    
};


template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::add_vertex(const vertex_t& v) {
    
    if(alists.find(v) == alists.end())
        alists[v] = alist_t();

}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::add_edge(const vertex_t& u, const vertex_t& v, const edge_t& e) {

    // Ensure that both u and v exists
    add_vertex(u);
    add_vertex(v);
    
    alists[u][v] = e;
}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::add_edge(const edge_t& e) {

    // Ensure that both u and v exists
    add_vertex(e.from);
    add_vertex(e.to);
    
    alists[e.from][e.to] = e;
}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::remove_vertex(const vertex_t& v){

    // Delete the vertex
    alists.erase(v);
    
    // Delete the vertex from other alists
    for(auto it = alists.begin(); it != alists.end(); it++)
        (it->second).erase(v);
    
}

template<typename vertex_t, typename edge_t>
inline void adj_list<vertex_t, edge_t>::remove_edge(const vertex_t& u, const vertex_t& v) {
    alists[u].erase(v);
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::indeg(const vertex_t& v) const {

    int deg = 0;
    for(auto it = alists.begin(); it != alists.end(); it++)
        if((it->second).find(v) != (it->second).end())
            deg++;
            
    return deg;
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::outdeg(const vertex_t& v) const {
    return alists.at(v).size();
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::num_vertices() const {
    return alists.size();
}

template<typename vertex_t, typename edge_t>
inline int adj_list<vertex_t, edge_t>::num_edges() const {

    int sum = 0;    
    for(auto it = alists.begin(); it != alists.end(); it++)
        sum += (it->second).size();
    return sum;
}


template<typename vertex_t, typename edge_t>
inline bool adj_list<vertex_t, edge_t>::are_adj(const vertex_t& u, const vertex_t& v) const {
    
    return alists.at(u).find(v) == alists.at(u).end();

}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_viterator adj_list<vertex_t, edge_t>::vbegin() {
    get_first<std::pair<vertex_t, alist_t>> trans;
    return boost::make_transform_iterator(alists.begin(), trans);
}
    
template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_viterator adj_list<vertex_t, edge_t>::vend() {
    get_first<std::pair<vertex_t, alist_t>> trans;
    return boost::make_transform_iterator(alists.end(), trans);
}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aviterator adj_list<vertex_t, edge_t>::avbegin(const vertex_t& u) {
    get_first<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].begin(), trans);
}



template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aviterator adj_list<vertex_t, edge_t>::avend(const vertex_t& u) { 
    get_first<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].end(), trans);
}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aeiterator adj_list<vertex_t, edge_t>::aebegin(const vertex_t& u) {
    get_second<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].begin(), trans);
}



template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_aeiterator adj_list<vertex_t, edge_t>::aeend(const vertex_t& u) { 
    get_second<std::pair<vertex_t, edge_t>> trans;
    return boost::make_transform_iterator(alists[u].end(), trans);
}


template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_eiterator adj_list<vertex_t, edge_t>::ebegin() {
    return const_eiterator(*this);
}



template<typename vertex_t, typename edge_t>
inline typename adj_list<vertex_t, edge_t>::const_eiterator adj_list<vertex_t, edge_t>::eend() { 
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

    friend std::ostream& operator<<(std::ostream& out, const_eiterator eit) {
        out << *(eit.aeit);
        return out;
    }

    const_eiterator() { }

 public:
    

    const_eiterator(adj_list<vertex_t, edge_t>& obj) : object(obj) {
        if(obj.alists.size() != 0) {
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
        return !(vit == other.vit && aeit == other.aeit) && !(vit == object.vend() && vit == other.vit);
    }

};

