#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

#define INF 10000
#define ISINF(x) (x) > INF ? true : false;

////////////////////////////////////////
//// Weighted Graph class //////
////////////////////////////////////////

class WeightedGraph {

		vector<vector<int>> adj_matrix;
		int total_vertices;

	public:
		WeightedGraph(int vertices);
		
		template<typename Iter>
		Iter get_vertices(Iter dest);

		int no_of_vertices();		
		
		template<typename Iter>
		Iter adjTo(int vertex, Iter dest);
		
		void add_edge(int u, int v, int w);
		int weight(int u, int v);
		
};

WeightedGraph::WeightedGraph(int vertices) {
	
	// Initialize total_vertices
	total_vertices = vertices;

	// Initialize the adj_matrix to all zeroes
	vector<int> infs(vertices);
	fill_n(infs.begin(), vertices, INF);
	for(int i = 0; i < vertices; i++)
		adj_matrix.push_back(infs);

}

template<typename Iter>
Iter WeightedGraph::get_vertices(Iter dest) {
	for(int i = 0; i < total_vertices; i++)
		*dest++ = i;
	return dest;
}

int WeightedGraph::no_of_vertices() {
	return total_vertices;
}

int WeightedGraph::weight(int u, int v) {
	return adj_matrix[u][v];
}

template<typename Iter>
Iter WeightedGraph::adjTo(int vertex, Iter dest) {
	/*
	for(int idx = 0; idx < total_vertices; idx++)
		if(adj_matrix[vertex][idx] == 1)
			*dest++ = idx;
	*/
	return dest;
}


void WeightedGraph::add_edge(int u, int v, int w) {
	
	adj_matrix[u][v] = w;
}


////////////////////////////////
// The class ends  /////////////
////////////////////////////////


template<typename Assoc_Cont>
Assoc_Cont& floyds_sp(WeightedGraph& G) {

	// !! Requires a container of that maps pair of vertices to an int as the temp-arg.
	
	Assoc_Cont& path_wt = *(new Assoc_Cont);
	
	int V = G.no_of_vertices();
	
	// Initialize the matrix
	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			if(i == j)
				path_wt[i][i] = 0;
			else if(G.weight(i, j) != -1)
				path_wt[i][j] = G.weight(i, j);
			else
				path_wt[i][j] = INF;
		}
	}
	
	vector<int> vertex_set(V);
	G.get_vertices(vertex_set.begin());
	
	for(int pivot : vertex_set) {
		// Relax all the paths that go through the pivot	
		
		for(int from : vertex_set)
			for(int to : vertex_set)
				if(path_wt[from][to] > path_wt[from][pivot] + path_wt[pivot][to])
					path_wt[from][to] = path_wt[from][pivot] + path_wt[pivot][to];
	
	}
	
	return path_wt;		
}


int main() {
	WeightedGraph G(4);
	G.add_edge(0, 1, 2);
	G.add_edge(1, 2, 4);
	G.add_edge(2, 3, 1);
	G.add_edge(2, 6, 6);
	G.add_edge(3, 0, 3);
	
	map<int, map<int, int>> path_wt;
	
	path_wt = floyds_sp<map<int, map<int, int>>>(G);
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			cout << path_wt[i][j] << "\t";
		cout << endl;
	}
	
}



