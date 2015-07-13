/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <set>
#include <alglib/graph/graph_property.h>

namespace alglib {
namespace graph {


/* GraphType must be undirected 
 */    
template<typename GraphType, typename OutputIter>
OutputIter prim_mst (const GraphType& G, OutputIter dest)
{
    using graph_type  = GraphType;
    using vertex_type = typename graph_type::vertex_type;
    using edge_type   = typename graph_type::edge_type;

    /* The edge set corresponding to a MST is directly loaded
     * onto the container referred by dest iterator */

	/* Maintain a set of edges that go out of the tree;
     * In each iteration, pick the lightest of them and include it in Tree */
    std::set<edge_type> protruding_edges;

    /* Keeps track of which vertices have been included in our incrementally
     * expanding tree. */
    vertex_property<graph_type, bool> included;

    int tree_size = 0;              // Instantaneous size of our tree = # of edges.
    int num_vertices = G.vsize ();  

    /* Intialization: 
     * Since the mst includes every every vertex, we can start with any vertex.
     * Let us choose to start with the vertex *G.vbegin (). Then, set included flag
     * to true and fill the protruding_edges set appropriately. */
    vertex_type start = *G.vbegin ();
    
    for (auto it = G.aebegin (start); it != G.aeend (start); it++)
        protruding_edges.insert (*it);

    included.set (start, true);

    while (tree_size != num_vertices - 1)
    {
        edge_type e = *protruding_edges.begin ();
        protruding_edges.erase (protruding_edges.begin());

        if (!included.get (e.to))
        {
            *dest++ = e;
            for (auto it = G.aebegin (e.to); it != G.aeend (e.to); it++)
                if (!included (it->to))
                    protruding_edges.insert (*it);
            ++tree_size;
        }
    }
    return dest;
}


}  // end of graph namespace
}  // end of alglib namespace

