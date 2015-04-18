


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
	
	disjoint_sets<graph::vertex_t> sets;
	
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
	}
	
	return res;
}
		
		

/**************************************************

Working Version


template<typename vertex_t, typename edge_t, typename OutputIter>
OutputIter kruskal_mst(undirected_graph<vertex_t, edge_t>& G, OutputIter res) { 

	disjoint_sets<vertex_t> sets;
	
	// vertex iterator
	for(typename undirected_graph<vertex_t, edge_t>::vertex_iter it = G.vbegin(); it != G.vend(); it++)
		sets.make_set(*it);
	
	std::list<edge_t> edges;
	
	// edge iterator
	for(typename undirected_graph<vertex_t, edge_t>::edge_iter it = G.ebegin(); it != G.eend(); it++)
		edges.push_back(*it);
		
	edges.sort();
		
	// expand and merge the components iteratively
	for(edge_t edge : edges) {
	
		vertex_t u = edge.either(), v = edge.other();
		
		if(sets.find_set(u) != sets.find_set(v)) {
			// Different component
			sets.unite(u, v);
			res++ = edge;
		}
	}
	
	return res;
}


struct edge_t {
	long long u;
	long long v;
	long long int wt;
	edge_t(long long a, long long b, long long weight) : u(a), v(b), wt(weight) { }
	long long  either() { return u; }
	long long other() { return v; }
	bool operator==(edge_t other) { return u == other.u and v == other.v; }
	bool operator<(edge_t other) { return  wt < other.wt; }
};

int main() {

	undirected_graph<long long, edge_t> g;
	
	long long n, m, u, v, wt;
	cin >> n >> m;
	while(m--) {
		cin >> u >> v >> wt;
		edge_t e(u, v, wt);
		g.add_edge(e);
	}
	
	vector<edge_t> mst;
	kruskal_mst(g, back_inserter(mst));
	
	long long cost = 0;
	for(edge_t edge : mst)
		cost += edge.wt;
		
	cout << cost << endl;
}




*******************************************************************************************************/








#endif
