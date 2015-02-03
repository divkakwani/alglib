#ifndef _GRAPH_ALGO_H
#define _GRAPH_ALGO_H

#include "../containers/graph.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <iterator>
#include <queue>

/*
The following function is templatized by vertex type (a subtype of Vertex class)
and a Sequence (linear).
*/
template<typename OutputIter>
OutputIter dfs_order(UndirectedGraph& G, OutputIter result) {
	/**
	This procedure fills the sequence pointed by the result iterator
	with the vertrices of the graph G traversed in depth-first order.
	**/
	std::unordered_map<Vertex*, bool, UndirectedGraph::Hasher> visited;
	std::vector<Vertex*> pvertex_list(G.no_of_vertices());
	G.get_vertices(pvertex_list.begin());

	for(auto& pvertex : pvertex_list)
		visited[pvertex] = false;	// Initially set all the vertices to unvisited

	for(auto& pvertex : pvertex_list) {
		if(!visited[pvertex])
			dfs(G, pvertex, visited, result);
	}
	return result;
}

template<typename OutputIter>
void dfs(UndirectedGraph& G, Vertex* start,
         std::unordered_map<Vertex*, bool, UndirectedGraph::Hasher>& visited,
         OutputIter& result) {
	/**
	This procedure traverses a component of the graph depth-first.
	**/
	typedef typename std::iterator_traits<OutputIter>::value_type val_type;

	visited[start] = true;
	*result++ = dynamic_cast<val_type>(start);

	std::vector<Vertex*> adjacent(10);
	auto last = G.adjTo(start, adjacent.begin());

	for(auto it = adjacent.begin(); it != last; it++) {
		if(!visited[*it])
			dfs(G, *it, visited, result);
	}
}


template<typename OutputIter>
OutputIter bfs_order(UndirectedGraph& G, OutputIter result) {
	/**
	This procedure traverses a component of the graph depth-first.
	**/
	typedef typename std::iterator_traits<OutputIter>::value_type val_type;

	std::queue<Vertex*> frontier;
	std::unordered_map<Vertex*, bool, UndirectedGraph::Hasher> visited;

	// Initialize visited
	std::vector<Vertex*> pvertex_list(G.no_of_vertices());
	G.get_vertices(pvertex_list.begin());
	for(auto& pvertex : pvertex_list)
		visited[pvertex] = false;	// Initially set all the vertices to unvisited

	for(auto& pvertex : pvertex_list) {

		if(!visited[pvertex])
			frontier.push(pvertex);

		while(!frontier.empty()) {
			Vertex* visiting = frontier.front();
			frontier.pop();
			visited[visiting] = true;
			*result++ = dynamic_cast<val_type>(visiting);

			std::vector<Vertex*> adjacent(10);
			auto last = G.adjTo(visiting, adjacent.begin());

			for(auto it = adjacent.begin(); it != last; it++) {
				if(!visited[*it])
					frontier.push(*it);
			}
		}
	}
	return result;
}



template<typename OutputIter>
OutputIter topological_sort(UndirectedGraph& G, OutputIter dest) {
	/**
		Fills the input container with the topological order.
	**/
}


template<typename OutputIter>
OutputIter connected_components(const Graph& G, OutputIter dest) {

}

// Dijikstra computes shortest path from single source to all vertex;
// So Dijiksta should run only once.
void dijskitra_shortest_path(const Graph& G) {

}


#endif
