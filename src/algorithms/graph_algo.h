#ifndef _GRAPH_ALGO_H
#define _GRAPH_ALGO_H

#include "../containers/graph.h"
#include "../containers/vertex.h"
#include "../containers/edge.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include <stack>

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

	std::vector<Vertex*> adjacent(10);
	auto last = G.adjTo(start, adjacent.begin());

	for(auto it = adjacent.begin(); it != last; it++) {
		if(!visited[*it])
			dfs(G, *it, visited, result);
	}
	
	*result++ = dynamic_cast<val_type>(start);
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
	
	typedef typename std::iterator_traits<OutputIter>::value_type val_type;

	std::vector<val_type> postorder(G.no_of_vertices());
	
	dfs_order(G, postorder.begin());
	
	return copy(postorder.rbegin(), postorder.rend(), dest);
	
}



template<typename OutputIter>
OutputIter connected_components(UndirectedGraph& G, OutputIter dest) {
	// dest must be an iterator to an associative container.
	// The output will be a mapping of a vertex to its componenet id (an int)
	
	
	std::unordered_map<Vertex*, bool, UndirectedGraph::Hasher> visited;
	std::vector<Vertex*> pvertex_list(G.no_of_vertices());
	G.get_vertices(pvertex_list.begin());

	for(auto& pvertex : pvertex_list)
		visited[pvertex] = false;	// Initially set all the vertices to unvisited


	std::vector<Vertex*> dfs_list(G.no_of_vertices());	
	
	std::vector<Vertex*>::iterator dfs_it = dfs_list.begin();
	int component_id = 0;
	
	for(auto& pvertex : pvertex_list) {
		auto prev_it = dfs_it;
		if(!visited[pvertex])
			dfs(G, pvertex, visited, dfs_it);
		for(auto it = prev_it; it != dfs_it; it++) {
			// somehow insert at the place where dest points
		}
		
	}
	return dest;

}

//  Future work
/*

template<typename InputIter>
OutputIter connected_components(const Graph& G, InputIter dfs_order) {


}


template<typename OutputIter>
OutputIter strongly_connected_components(const DirectedGraph& G, OutputIter dest) {
	// dest must be an iterator to an associative container.
	// The output will be a mapping of a vertex to its componenet id (an int)
	

}


// Helper function for shortest paths algorithm
static void relax(const Graph& G, Edge& e) {
	

} 


void Bellman_Ford(const Graph& G, Vertex* source, OutputIter dest) {

}


void dijskitra_shortest_path(const Graph& G, Vertex* source, OutputIter dest) {
	// dest must be an iterator to an associative iterator.

}

*/



#endif
