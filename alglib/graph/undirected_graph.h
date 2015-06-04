/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#include <alglib/graph/edge.h>
#include <alglib/graph/adj_list.h>

#pragma once

template<typename vertex_t, typename attr_t = void, 
         template<typename, typename> class model = adj_list>
class undirected_graph : public model<vertex_t, edge_t<vertex_t, attr_t>> {

    typedef model<vertex_t, edge_t<vertex_t, attr_t>> super;
 public:
    typedef edge_t<vertex_t, attr_t> edge_type;

    void add_edge(const vertex_t& u, const vertex_t& v, const attr_t& attr) {
        super::add_edge(u, v, edge_type(u, v, attr));
        super::add_edge(v, u, edge_type(v, u, attr));
    }
};

// Partial specialzation for void attributes (or not attributes)
template<typename vertex_t, template<typename, typename> class model>
class undirected_graph<vertex_t, void, model> : public model<vertex_t, edge_t<vertex_t>> {
    
    typedef model<vertex_t, edge_t<vertex_t, void>> super;
 public:
    typedef edge_t<vertex_t, void> edge_type;

    void add_edge(const vertex_t& u, const vertex_t& v) {
        super::add_edge(u, v, edge_type(u, v));
        super::add_edge(v, u, edge_type(v, u));
    }
};





