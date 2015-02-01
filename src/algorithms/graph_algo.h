#ifndef _GRAPH_ALGO_H
#define _GRAPH_ALGO_H

#include "../containers/graph.h"
#include <map>
#include <iostream>
#include <vector>

/*
The following function is templatized by vertex type (a subtype of Vertex class)
and a Sequence (linear).
*/
template<typename OutputIter>
void dfs_order(UndirectedGraph& G, OutputIter result) {
	/**
	This procedure fills the sequence pointed by the start iterator
	with the vertrices of the graph G traversed in depth-first order.
	**/
	std::map<Vertex*, bool> visited;
	std::set<Vertex*> vertex_list = G.get_vertices<Vertex*>();

	for(auto& pvertex : vertex_list) {
		// Initially set all the vertices to unvisited
		visited[pvertex] = false;
	}

	for(auto& pvertex : vertex_list) {
		//std::cout << pvertex << "\t" << *result << std::endl;
		if(!visited[pvertex])
			dfs(G, pvertex, visited, result);
	}
}
template<typename OutputIter>
void dfs(UndirectedGraph& G, Vertex* start, std::map<Vertex*, bool>& visited, OutputIter result) {
	/**
	This procedure traverses a component of the graph depth-first.
	**/

	visited[start] = true;
	*result = start;
	result++;
	std::vector<Vertex*> adjacent = G.adjTo<Vertex*>(start);
	for(auto& pvertex : adjacent) {
		if(!visited[pvertex])
			dfs(G, pvertex, visited, result);
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
