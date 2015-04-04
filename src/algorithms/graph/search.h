
#ifndef _GRAPH_SEARCH_H
#define _GRAPH_SEARCH_H

#include "../../containers/graph/graph.h"
#include "../../containers/graph/vertex.h"
#include "../../containers/graph/edge.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include <stack>

template<typename OutputIterator>
OutputIterator dfs_order(graph& G, OutputIterator dest) {

	/**
	This procedure fills the sequence pointed by the result iterator
	with the vertrices of the graph G traversed in depth-first order.
	**/
	
	/* Keeps a record of the vertices visited */
	std::unordered_map<Vertex*, bool, graph::Hasher> visited;
	
	/* pvertex_list stores all the vertices of the graph */
	std::vector<Vertex*> pvertex_list;
	G.get_vertices(std::back_inserter(pvertex_list));

	for(Vertex* pvertex : pvertex_list)
		visited[pvertex] = false;	// Initially set all the vertices to unvisited

	for(Vertex* pvertex : pvertex_list) {
		if(!visited[pvertex])
			dest = dfs(G, pvertex, visited, dest);
	}
	return dest;
}




template<typename OutputIterator>
void dfs(graph& G, Vertex* start,
         std::unordered_map<Vertex*, bool, graph::Hasher>& visited,
         OutputIterator dest) {
         
	/**
	This procedure traverses a component of the graph depth-first.
	**/
	
	typedef typename std::iterator_traits<OutputIterator>::value_type val_type;

	visited[start] = true;

	std::vector<Vertex*> adjacent;
	G.adjTo(start, std::back_inserter(adjacent));

	for(auto it = adjacent.begin(); it != adjacent.end(); it++) {
		if(!visited[*it])
			dest = dfs(G, *it, visited, dest);
	}
	
	*dest++ = dynamic_cast<val_type>(start);
	
	return dest;
}





template<typename OutputIterator>
OutputIterator bfs_order(graph& G, OutputIterator dest) {

	/**
	This procedure traverses a component of the graph breadth-first.
	**/
	
	typedef typename std::iterator_traits<OutputIterator>::value_type val_type;

	/* Stores all the vertices that have equal internodal distance with the source */
	std::queue<Vertex*> frontier;
	std::unordered_map<Vertex*, bool, graph::Hasher> visited;

	// Initialize visited
	std::vector<Vertex*> pvertex_list;
	G.get_vertices(std::back_inserter(pvertex_list));
	
	for(Vertex* pvertex : pvertex_list)
		visited[pvertex] = false;	// Initially set all the vertices to unvisited

	for(Vertex* pvertex : pvertex_list) {

		if(!visited[pvertex])
			frontier.push(pvertex);

		while(!frontier.empty()) {
			Vertex* visiting = frontier.front();
			frontier.pop();
			visited[visiting] = true;
			*dest++ = dynamic_cast<val_type>(visiting);

			std::vector<Vertex*> adjacent;
			G.adjTo(visiting, std::back_inserter(adjacent));

			for(Vertex* it = adjacent.begin(); it != adjacent.end(); it++) {
				if(!visited[*it])
					frontier.push(*it);
			}
		}
	}
	return dest;
}



#endif
