/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <queue>
#include <alglib/graph/graph_property.h>


namespace alglib {
namespace graph {

template<typename GraphType, typename OutputIter>
OutputIter _single_bfs(const GraphType& G,
               const typename GraphType::vertex_type& start,
               vertex_property<GraphType, bool>& visited,
               OutputIter dest) {    
    
    typedef typename GraphType::vertex_type vertex_type;

    /* Maintains a list of unexplored vertices in order of their distance
     * from the start vertex */
    std::queue<vertex_type> frontier;

    /* Put `start` in the queue to start the bfs from */
    frontier.push(start);
    
    while(!frontier.empty()) {
        vertex_type inspect = frontier.front();
        frontier.pop();
        visited[inspect] = true;

        /* Put it into the output stream before inspection */
        *dest++ = inspect;

        for(auto it = G.avbegin(inspect); it != G.avend(inspect); it++)
            if(!visited(*it))
                frontier.push(*it);
    }
    return dest;
}

template<typename GraphType, typename OutputIter>
OutputIter single_bfs(const GraphType& G,
               const typename GraphType::vertex_type& start,
               OutputIter dest) {    
    return _single_bfs(G, start, vertex_property<GraphType, bool>(G, false), dest);
}


template<typename GraphType, typename OutputIter>
OutputIter bfs(const GraphType& G, 
               const typename GraphType::vertex_type& start,
               OutputIter dest) {
    
    /* visited property initialized with false for each vertex */
    vertex_property<GraphType, bool> visited(G, false);

    /* do the bfs of the start vertex first */
    dest = _single_bfs(G, start, visited, dest);

    /* then others if they are not visited */
    for(auto it = G.vbegin(); it != G.vend(); it++)
        if(!visited(*it))
            dest = _single_bfs(G, *it, visited, dest);

    return dest;
}


template<typename GraphType, typename OutputIter>
OutputIter bfs(const GraphType& G, OutputIter dest) {
    return bfs(G, *G.vbegin(), dest);
}
    

}  // end of graph namespace
}  // end of alglib namespace


