#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>


using namespace std;



/**
Algorithm
	1. Export the graph object to an adjacency matrix.
	2. Find the vertices which have 0 in-degree.
	3. Add them to a queue.
	
	Servicing a queue
	
	1. Deque an element off the queue
	2. Remove all the edges emnating from the element.
	3. Add the element to topological order.
	4. For every edge u-v emnating from u :
			delete_edge(u, v)
			if(in-degree(v) == 0)
				add v to the queue.
**/


/**
Operations on the graph required.
  in-degree(v) - Read and write
  out-degree(v) - Read and write
  edge deletion 
  adj(v)
  
**/


class DynamicDirectedGraph {

		vector<vector<int>> adj_matrix;
		int total_vertices;
		vector<int> indeg;
		vector<int> outdeg;
		
		// should the number of vertices also be dynamic? 

	public:
		DynamicDirectedGraph(int vertices);
		
		template<typename Iter>
		Iter get_vertices(Iter dest);

		int no_of_vertices();		
		
		template<typename Iter>
		Iter adjTo(int vertex, Iter dest);
		
		void add_edge(int u, int v);
		
		void delete_edge(int u, int v);
		
		int in_degree(int vertex);
		int out_degree(int vertex);
		
};

DynamicDirectedGraph::DynamicDirectedGraph(int vertices) {
	
	// Initialize total_vertices
	total_vertices = vertices;

	// Initialize the adj_matrix to all zeroes
	vector<int> zeroes(vertices);
	fill_n(zeroes.begin(), vertices, 0);
	for(int i = 0; i < vertices; i++)
		adj_matrix.push_back(zeroes);

	// Initialize the indeg and outdeg vectors to all zeroes
	fill_n(back_inserter(indeg), vertices, 0);
	fill_n(back_inserter(outdeg), vertices, 0);
}

template<typename Iter>
Iter DynamicDirectedGraph::get_vertices(Iter dest) {
	for(int i = 0; i < total_vertices; i++)
		*dest++ = i;
	return dest;
}

int DynamicDirectedGraph::no_of_vertices() {
	return total_vertices;
}

template<typename Iter>
Iter DynamicDirectedGraph::adjTo(int vertex, Iter dest) {
	for(int idx = 0; idx < total_vertices; idx++)
		if(adj_matrix[vertex][idx] == 1)
			*dest++ = idx;
	return dest;
}


void DynamicDirectedGraph::add_edge(int u, int v) {
	
	adj_matrix[u][v] = 1;
	outdeg[u]++;
	indeg[v]++;
}

void DynamicDirectedGraph::delete_edge(int u, int v) {
	adj_matrix[u][v] = 0;
	outdeg[u]--;
	indeg[v]--;
}

int DynamicDirectedGraph::in_degree(int u) {
	return indeg[u];
}

int DynamicDirectedGraph::out_degree(int u) {
	return outdeg[u];
}


template<typename Iter>
Iter source_removal(DynamicDirectedGraph& G, Iter dest) {
	queue<int> q;
	vector<int> vertices(G.no_of_vertices());
	
	auto last = G.get_vertices(vertices.begin());
	for(auto it = vertices.begin(); it != last; it++)
		if(G.in_degree(*it) == 0)
			q.push(*it);
	
	
	int processed_vertices = 0;
	
	while(!q.empty()) {
		int visit = q.front();
		q.pop();
		processed_vertices++;
		
		*dest++ = visit;	// Push the element to final list
		
		vector<int> adj(G.no_of_vertices());
		auto last = G.adjTo(visit, adj.begin());
		for(auto it = adj.begin(); it != last; it++) {
			G.delete_edge(visit, *it);
			if(G.in_degree(*it) == 0)
				q.push(*it);
		}	 
	}
	
	assert(processed_vertices == G.no_of_vertices());
	
	
	return dest;
}


int main() {
	DynamicDirectedGraph G(6);
	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.add_edge(1, 2);
	G.add_edge(3, 0);
	G.add_edge(4, 3);
	G.add_edge(4, 0);
	G.add_edge(5, 0);
	G.add_edge(5, 2);
	G.add_edge(5, 4);
	
	
	vector<int> top_order(G.no_of_vertices());
	vector<int>::iterator last = source_removal(G, top_order.begin());	
	for(auto elt : top_order)
		cout << elt << endl;
	
	return 0;
}

