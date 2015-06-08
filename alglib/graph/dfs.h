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

namespace alglib {
namespace graph {

/*
 * \brief Does a single preorder dfs on G starting from `start`
 *
 * It is intended to be used inside the preorder dfs function. For that reason,
 * another argument visited is provided to maintain the vertices visited so far.
 */
template<typename GraphType, typename OutputIter>
OutputIter _single_preorder_dfs(const GraphType& G,
                                const typename GraphType::vertex_type& start,
                                vertex_property<GraphType, bool>& visited,
                                OutputIter dest) {
    *dest++ = start;  // Put it on the output stream
    visited[start] = true;

    /* Explore adjacent vertices */
    for(auto it = G.avbegin(start); it != G.avend(start); it++)
        if(!visited(*it))
            dest = _single_preorder_dfs(G, *it, visited, dest);

    return dest;
}


template<typename GraphType, typename OutputIter>
OutputIter single_preorder_dfs(const GraphType& G,
                               const typename GraphType::vertex_type& start,
                               OutputIter dest) {
    vertex_property<GraphType, bool> visited(G, false);
    return _single_preorder_dfs(G, start, visited, dest);
}

template<typename GraphType, typename OutputIter>
OutputIter _single_postorder_dfs(const GraphType& G,
                                 const typename GraphType::vertex_type& start,
                                 vertex_property<GraphType, bool>& visited,
                                 OutputIter dest) {
    visited[start] = true;
    for(auto it = G.avbegin(start); it != G.avend(start); it++)
        if(!visited(*it))
            dest = _single_postorder_dfs(G, *it, visited, dest);
    *dest++ = start;  // Put it on the output stream
    return dest;
}

template<typename GraphType, typename OutputIter>
OutputIter single_postorder_dfs(const GraphType& G,
                               const typename GraphType::vertex_type& start,
                               OutputIter dest) {
    vertex_property<GraphType, bool> visited(G, false);
    return _single_postorder_dfs(G, start, visited, dest);
}

template<typename GraphType, typename OutputIter>
OutputIter preorder_dfs(const GraphType& G, 
                        const typename GraphType::vertex_type start,
                        OutputIter dest) {

    /* visited property, initialized with false for each vertex */
    vertex_property<GraphType, bool> visited(G, false);

    /* do a dfs on the start vertex first */
    dest = _single_preorder_dfs(G, start, visited, dest);

    /* check all the vertices and perform dfs on the unvisited ones */
    for(auto it = G.vbegin(); it != G.vend(); it++)
        if(!visited(*it))
            dest = _single_preorder_dfs(G, *it, visited, dest);

    return dest;
}

template<typename GraphType, typename OutputIter>
OutputIter preorder_dfs(const GraphType& G, OutputIter dest) {
    return preorder_dfs(G, *G.vbegin(), dest);
}


template<typename GraphType, typename OutputIter>
OutputIter postorder_dfs(const GraphType& G,
                         const typename GraphType::vertex_type start,
                         OutputIter dest) {

    /* visited property on G, each initialized with false */
    vertex_property<GraphType, bool> visited(G, false);

    /* do a dfs on the start vertex first */
    dest = _single_postorder_dfs(G, start, visited, dest);

    /* check all the vertices and perform dfs on the unvisited ones */
    for(auto it = G.vbegin(); it != G.vend(); it++)
        if(!visited(*it))
            dest = _single_postorder_dfs(G, *it, visited, dest);

    return dest;
}


template<typename GraphType, typename OutputIter>
OutputIter postorder_dfs(const GraphType& G, OutputIter dest) {
    return postorder_dfs(G, *G.vbegin(), dest);
}

}  // end of graph namespace
}  // end of alglib namespace

