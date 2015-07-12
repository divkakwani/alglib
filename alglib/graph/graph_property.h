/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <map>
#include <stdexcept>
#include <ostream>
#include <boost/optional.hpp>

namespace alglib {
namespace graph {

template<typename graph_t, typename property_t>
class vertex_property
{
 public:

    /* type aliases */
    using vertex_type   = typename graph_t::vertex_type;
    using property_type = property_t; 
    using graph_type    = graph_t;

 private:

    /* The value of the property map is optional<property_type>, a type
     * similar to Maybe<T> in Haskell. This allows the property value to
     * be NIL, which is required by some algorithms.
     */
    std::map<vertex_type, boost::optional<property_type>> property_map;
    
    using property_map_iter 
             = typename std::map<vertex_type, boost::optional<property_type>>::iterator;

 public:

    vertex_property () = delete;

    /**
     * \breif Initializes the property of each of the vertex to boost::none;
     */
    explicit vertex_property (const graph_type& G)
    {
        for (auto it = G.vbegin (); it != G.vend (); it++)
            property_map[*it] = boost::none;
    }

    /** 
     * \brief vertex_property constructor 
     * \param G The graph on which the property is to be defined
     * \param default_val (optional) Default property of each vertex
     */
    explicit vertex_property (const graph_type& G, 
                              const property_type& default_val)
    {
        for (auto it = G.vbegin(); it != G.vend(); it++)
            property_map[*it] = default_val;
    }
    
    
    vertex_property (const vertex_property& P) = default;

    /**
     * \brief move-constructor
     */
    vertex_property (vertex_property&& P) : property_map (std::move (P.property_map)) {}

    /**
     * \brief get the reference to the property associated with a vertex
     * \param v vertex whose property is sought
     * \return A reference to the property of the vertex
     */
    property_type& operator[] (const vertex_type& v) 
    {
        return property_map.at (v);
    }

    property_type operator() (const vertex_type& v) const
    { 
        return property_map.at (v);
    }

    /**
     * \brief Update the property of many vertices at once.
     */
    template<typename InputIter>
    void bulk_update (InputIter first, InputIter last, const property_type& val) 
    {
        while (first != last)
        {
            property_map.at(*first) = val;
            ++first;
        }
    }

    friend std::ostream& operator<< (std::ostream& out, const vertex_property& P)
    {
        for (auto it = P.property_map.cbegin(); it != P.property_map.cend(); it++) 
        {
            out << "(" << it->first << ": " << it->second << ")\n";
        }
    }
};



template<typename GraphType, typename PropertyType>
class edge_property {
    
 public:

    /* typedefs */
    typedef typename GraphType::edge_type edge_type;
    typedef PropertyType property_type;
    typedef GraphType graph_type;

 private:
    std::map<edge_type, PropertyType> property;

 public:
    
    explicit edge_property(const GraphType& G,
                           const PropertyType& default_val = PropertyType()) {
        for(auto it = G.ebegin(); it != G.eend(); it++)
            property[*it] = default_val;
    }
    
    explicit edge_property(const edge_property& P) = default;

    /*
     * \brief move-constructor
     */
    explicit edge_property(edge_property&& P) : property(std::move(P.property)) {}

    /*
     * \brief get the reference to the property associated with a vertex
     * \param v vertex whose property is sought
     * \return A reference to the property of the vertex
     */
    PropertyType& operator[] (const edge_type& v) {
        typename std::map<edge_type, PropertyType>::iterator it;
        if((it = property.find(v)) == property.end())
            throw std::domain_error("The edge doesn't exist in the supplied graph");
        return it->second;
    }

    PropertyType operator() (const edge_type& v) const { 
        typename std::map<edge_type, PropertyType>::const_iterator it;  // const-ness imperative
        if((it = property.find(v)) == property.end())
            throw std::domain_error("The edge doesn't exist in the supplied graph");
        return it->second;
    }

    /*
     * \brief Update the property of many edges at once.
     */
    template<typename InputIter>
    void bulk_update(InputIter first, InputIter last, property_type val) {
        while(first != last) {
            property.at(*first) = val;
            ++first;
        }
    }

    friend std::ostream& operator<< (std::ostream& out, const edge_property& P) {
        for(auto it = P.property.cbegin(); it != P.property.cend(); it++) 
            out << "(" << it->first << ": " << it->second << ")\n";
    }
};


}  // end of graph namespace
}  // end of alglib namespace
