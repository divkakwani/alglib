/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


#pragma once

#include <alglib/heap/binary_heap.h>
#include <alglib/graph/graph_property.h>
#include <alglib/graph/edge.h>
#include <limits>


namespace alglib {
namespace graph {


struct get_attr {
    template<typename vertex_t, typename attr_t>
    attr_t operator() (const edge_t<vertex_t, attr_t>& a) {
        return a.attribute;
    };
};

/**
 * \brief The dijkstra's single-source shortest path algorithm.
 *
 * The cost associated with each edge MUST BE positive.
 *
 */
template<typename GraphType, typename Cost = get_attr>
vertex_property<GraphType, typename std::result_of<Cost(typename GraphType::edge_type)>::type>
dijkstra(const GraphType& G,
         const typename GraphType::vertex_type& source) {

    typedef typename std::result_of<Cost(typename GraphType::edge_type)>::type PropType;

    // cost functor
    Cost cost;
    
    vertex_property<GraphType, PropType> D(G, std::numeric_limits<PropType>::max());
   
    D[source] = 0;
    
    alglib::heap::keyed_binary_heap<typename GraphType::vertex_type, PropType> estimates;
    
    // insert initial estimate of source - which is 0. No need to add other vertices in
    // estimates at the moment; they'll be added as the edges get relaxed. If a vertex never
    // gets added into estimates, then its D value never changes - it always remains infinity,
    // which is exactly what is required.
    estimates.insert(source, D[source]);

    while(!estimates.empty()) {
        
        typename GraphType::vertex_type u = estimates.get_min_elt();
        estimates.delete_min();

        // relax all the edges outgoing from u
        for(auto it = G.aebegin(u); it != G.aeend(u); it++)
            if(D[it->from] + cost(*it) < D[it->to]) {
                D[it->to] = D[it->from] + cost(*it);
                estimates.update_key(it->to, D[it->to]);
            }      
    }
    return D;
}


}  // end of graph namespace
}  // end of alglib namespace
