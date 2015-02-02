#ifndef _GRAPH_ALGO_H
#define _GRAPH_ALGO_H

#include "../containers/graph.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <iterator>

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

/*
vector<Vertex*> list;
dfs(G, list.begin());





for(Vertex v : dfs(G)) {

}
*/

/*

template<typename vertex_type, template<typename T> Seq<T>>
Seq<Seq<vertex_type>> connected_components(const Graph& G);

template<typename Vertex, template<typename T> Seq<T>>
Seq<Vertex> dijskitra_shortest_path(const Graph& G, Vertex source, Vertex Destination);

**/
#endif
