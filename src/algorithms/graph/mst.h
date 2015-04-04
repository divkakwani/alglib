


#ifndef _MST_H
#define _MST_H

/*
	Contract:
		Input  : Graph G
		Output : A list of edges that make up a minimum spanning tree.

*/

/* Type expectation of Graph
	
	iterators - vertex and edge
	
	
*/
template<typename OutputIter>
OutputIter kruskal_mst(graph& G, OutputIter res) { 

	/*
		The 
	*/
	
	disjoint_sets sets;
	
	// vertex iterator
	for(graph::vertex_iter it = G.vbegin(); it != G.vend(); it++) {
		sets.make_set(*it);
	}
	
	std::list<Graph::edge_type> edges;
	
	// edge iterator
	for(graph::edge_iter it = G.ebegin(); it != G.eend(); it++)
		edges.push_back(*it);
		
	edges.sort();
	
	// expand and merge the components iteratively
	for(graph::edge_type edge : edges) {
	
		graph::vertex_type u = edge.either(), v = edge.other();
		
		if(sets.find(u) != sets.find(v)) {
			// Different component
			sets.unite(u, v);
			res++ = edge;
	}
	
	return res;
}
		
		



#endif
