/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <alglib/graph/graph_property.h>
#include <alglib/graph/dfs.h>
#include <vector>

namespace alglib {
namespace graph {

template<typename GraphType>
vertex_property<GraphType, int> connected_components(const GraphType& G) {
    /* initialize each property with -1, indicating its component has not been ascertained */
    vertex_property<GraphType, int> component_id(G, -1);

    /* start labelling component id with 1 */
    int next_component_id = 1;

    for(auto it = G.vbegin(); it != G.vend(); it++) {
        /* for every vertex which is not assigned a component id */
        if(component_id(*it) == -1) {
            std::vector<typename GraphType::vertex_type> component;
            single_preorder_dfs(G, *it, back_inserter(component));

            /* set the component_id of each of the vertices in component */
            for(auto vertex : component)
                if(component_id(vertex) == -1)
                    component_id[vertex] = next_component_id;

            next_component_id++;
        }
    }
    return component_id;
};

}  // end of graph namespace
}  // end of alglib namespace

