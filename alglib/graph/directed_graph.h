/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#include <alglib/graph/models/adj_list.h>
#include <alglib/graph/edge.h> 

#pragma once

namespace alglib {
namespace graph {

template<typename vertex_t, typename attr_t = void,
         template<typename, typename> class model = models::adj_list>
class directed_graph : public model<vertex_t, edge_t<vertex_t, attr_t>> {

 public:
    typedef edge_t<vertex_t, attr_t> edge_type;

    void add_edge(const vertex_t& u, const vertex_t& v, const attr_t& attr) {
        model<vertex_t, edge_type>::add_edge(u, v, edge_type(u, v, attr));
    }

};


template<typename vertex_t,
         template<typename, typename> class model>
class directed_graph<vertex_t, void, model> : public model<vertex_t, edge_t<vertex_t>> {

 public:    
    typedef edge_t<vertex_t, void> edge_type;
    
    void add_edge(const vertex_t& u, const vertex_t& v) {
        model<vertex_t, edge_type>::add_edge(u, v, edge_type(u, v));
    }

};

}  // end of graph namespace
}  // end of alglib namespace

