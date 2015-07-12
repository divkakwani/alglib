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
#include <stack>


namespace alglib {
namespace graph {


template<typename edge_t>
struct get_attr 
{
    typename edge_t::attr_type operator() (const edge_t& e) const { return e.attribute; }
};

/**
 * \brief The dijkstra's single-source shortest path algorithm.
 *
 * The cost associated with each edge MUST BE positive.
 *
 */
template <typename graph_type, typename cost_funct = get_attr<typename graph_type::edge_type>>
class dijkstra {
 
 public:
    
    using vertex_type = typename graph_type::vertex_type;
    using edge_type   = typename graph_type::edge_type;
    using cost_type   = typename std::result_of<cost_funct (edge_type)>::type;

    dijkstra (const graph_type& G, const vertex_type& src, 
              const cost_funct& cost = get_attr<edge_type>());

    template<typename OutputIter>
    OutputIter shortest_path_to (const vertex_type& dest, OutputIter output) const;

    cost_type  shortest_dist_to (const vertex_type& dest) const; 


 private:

    vertex_property<graph_type, cost_type> min_dist; 
    vertex_property<graph_type, vertex_type> predecessor;
    vertex_type source;
};


template<typename graph_type, typename cost_funct>
dijkstra<graph_type, cost_funct>::dijkstra (const graph_type& G, 
                                            const typename graph_type::vertex_type& src,
                                            const cost_funct& cost)
                                            : min_dist (G, std::numeric_limits<cost_type>::max ()),
                                              source (src),
                                              predecessor (G)
{
    min_dist.set(src, 0);
    predecessor.set (src, src);
    
    alglib::heap::keyed_binary_heap<vertex_type, cost_type> estimates;
    
    /* insert initial estimate of source - which is 0. No need to add other vertices in
     * estimates at the moment; they'll be added as the edges get relaxed. If a vertex never
     * gets added into estimates, then its D value never changes - it always remains infinity,
     * which is exactly what is required.
     */
    estimates.insert (src, 0);

    while (!estimates.empty ()) 
    {   
        vertex_type u = estimates.get_min_elt ();
        estimates.delete_min ();

        // relax all the edges outgoing from u
        for (auto it = G.aebegin(u); it != G.aeend(u); it++)
        {
            if (min_dist.get (it->from) + cost(*it) < min_dist.get (it->to)) 
            {
                min_dist.set(it->to, min_dist.get (it->from) + cost (*it));
                predecessor.set (it->to, it->from);

                estimates.update_key (it->to, min_dist.get (it->to));
            }
        }
    }
}


template<typename graph_type, typename cost_funct>
template<typename OutputIter>
OutputIter dijkstra<graph_type, cost_funct>::shortest_path_to (const vertex_type& dest,
                                                               OutputIter output) const
{
    if (!predecessor.is_initialized (dest))
        return output;

    std::stack<vertex_type> stack;

    for (vertex_type u = dest; u != source; u = predecessor.get (u))
    {
        stack.push (u);
    }
    
    *output++ = source;
    while (!stack.empty ())
    {
        *output++ = stack.top ();
        stack.pop ();
    }
    return output;
}

template<typename graph_type, typename cost_funct>
typename dijkstra<graph_type, cost_funct>::cost_type
dijkstra<graph_type, cost_funct>::shortest_dist_to (const vertex_type& dest) const
{
    return min_dist.get (dest);
}



/* // Partial specialization for default cost_funct */
/* template<typename graph_type> */
/* class dijkstra<graph_type, get_attr<typename graph_type::edge_type>> */



}  // end of graph namespace
}  // end of alglib namespace
