/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <alglib/graph/edge.h>
#include <alglib/graph/graph_property.h>
#include <limits>

namespace alglib {
namespace graph {

/* Shortest Path algorithms
 * The shortest path algorithms use a notion of cost, associated with each edge, and that
 * the cost associated with a path is the sum of the costs of the constituent edges.
 * The graph classes do not explicity have a cost field associated with every edge. It has an
 * attribute field which can store anything - cost, name label, or anything composite. But for 
 * them to be used in shortest path algorithms, they must supply some cost-like parameter 
 * associated with every edge. For this reason, shortest path functions take an aditional
 * parameter, Cost, a functor that extracts cost out of an edge. The value returned by it must
 * be comparable and add-able.
 * The ssp functions return a vertex property associating with every vertex the cost of the least
 * expensive path. 
 */


struct get_attr {
    template<typename vertex_t, typename attr_t>
    attr_t operator() (const edge_t<vertex_t, attr_t>& a) {
        return a.attribute;
    };
};

/** 
 * \brief The Bellman-Ford single-source shortest path algorithm. 
 *
 */
template<typename GraphType, typename Cost = get_attr>
vertex_property<GraphType, typename std::result_of<Cost(typename GraphType::edge_type)>::type> 
bellman_ford(const GraphType& G, 
             const typename GraphType::vertex_type& source) {


    int sz = G.num_vertices();

    typedef typename std::result_of<Cost(typename GraphType::edge_type)>::type PropType;

    Cost cost;

    vertex_property<GraphType, PropType> D(G, std::numeric_limits<PropType>::max());

    // set source distance to zero
    D[source] = 0; 

    for(int i = 0; i < sz; i++)
        for(auto it = G.ebegin(); it != G.eend(); it++) {
            if(D[(*it).from] + cost(*it) < D[(*it).to])
                D[(*it).to] = D[(*it).from] + cost(*it);

        }

    return D;

}


}  // end of graph namespace
}  // end of alglib namespace
