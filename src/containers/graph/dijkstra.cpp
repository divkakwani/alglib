#include <bits/stdc++.h>
using namespace std;	


/*
class vertex_iterator
	:	public std::iterator<std::bidirectional_iterator_tag,
							type, std::ptrdiff_t
							
*/						

template<typename vertex_type, typename edge_type> class undirected_graph {

	public:	
		typedef vertex_type 							vertex_t;
		typedef edge_type 								edge_t;
		typedef typename vector<edge_t>::iterator 		edge_iter;
		typedef typename vector<vertex_t>::iterator 	vertex_iter;
	
	private:
		map<vertex_t, vector<vertex_t>>  adjacency_list;
		map<vertex_t, vector<edge_t>>	 adjacency_edge;
		vector<vertex_t> 				 vertex_list;
		vector<edge_t> 					 edge_list;
		
	public:

		void add_vertex(vertex_t vertex) {
			if(adjacency_list.find(vertex) == adjacency_list.end()) {
				adjacency_list[vertex] = vector<vertex_t>();
				adjacency_edge[vertex] = vector<edge_t>();
				vertex_list.push_back(vertex);
			}
		}
		void add_edge(edge_t e) {
			if(find(edge_list.begin(), edge_list.end(), e) == edge_list.end()) {
				vertex_t u = e.either(), v = e.other();
				add_vertex(u);
				add_vertex(v);
				adjacency_list[u].push_back(v);
				adjacency_list[v].push_back(u);
				adjacency_edge[u].push_back(e);
				adjacency_edge[v].push_back(e);
				edge_list.push_back(e);
			}
		}		
				
		auto vbegin() {
			return vertex_list.begin();
		}
		
		auto vend() {
			return vertex_list.end();
		}
		
		auto ebegin() {
			return edge_list.begin();
		}
		auto eend() {
			return  edge_list.end();
		}
		
		auto avbegin(vertex_t vertex) {
			return adjacency_list[vertex].begin();
		
		}
		
		auto avend(vertex_t vertex) {
			return adjacency_list[vertex].end();
		}
		
		auto aebegin(vertex_t vertex) {
			return adjacency_edge[vertex].begin();
		
		}
		
		auto aeend(vertex_t vertex) {
			return adjacency_edge[vertex].end();
		}
	
	

};



template<typename graph>
class dijkstra_sssp {

		typedef typename graph::vertex_t vertex_t;
		graph& G;
		vertex_t src;
		unordered_map<vertex_t, long long> dist;
		
	public:
		
		dijkstra_sssp(graph& g, vertex_t source);
		
		long long dist_to(vertex_t dest);

};

/*
concept graph {
	vbegin();
	vend();
	aebegin();
	aeend();
};

concept edge {
	vertex  u;
	vertex  v;
	int     wt;
};
*/

template<typename graph>
dijkstra_sssp<graph>::dijkstra_sssp(graph& g, vertex_t source) : G(g), src(source) {

	const int inf = 1000000000;	// A constexpr - evaled at compile-time.
	
	// The set E stores our best estimate for the shortest path to each vertex.
	// The one with the least estimate is transferred to the set S and all the edges leaving it are relaxed
	set<pair<int, vertex_t>> E;	// ordered by distance

	for(auto it = G.vbegin(); it != G.vend(); it++) {
		dist[*it] = inf;
	}	

	dist[source] = 0;
	E.insert(make_pair(dist[source], source));
	
	while(!E.empty()) {
		pair<int, vertex_t> least = *E.begin();
		E.erase(*E.begin());
		
		int path_len = least.first;
		vertex_t u = least.second;
		
		// TODO : segregate relax procedure
		
		// relax all the outbound edges
		for(auto it = G.aebegin(u); it != G.aeend(u); it++) {
		
			vertex_t v = it->to();
			int wt = it->weight();
			
			// Improve estimate
			if(dist[u] + wt < dist[v]) {
				typename set<pair<int, vertex_t>>::iterator it;
				if((it = E.find(make_pair(dist[v], v))) != E.end())
					E.erase(it);
				dist[v] = dist[u] + wt;
				E.insert(make_pair(dist[v], v));
			}
		}
	}	
	
}

template<typename graph>
long long dijkstra_sssp<graph>::dist_to(vertex_t dest) {
	if(dest == src)
		return 0;
	else if(dist[dest] == 0 or dist[dest] > 100000000)
		return -1;
	return dist[dest];
}








		
struct edge_t {
	long long u;
	long long v;
	long long int wt;
	edge_t(long long a, long long b, long long weight) : u(a), v(b), wt(weight) { }
	long long  from() { return u; }
	long long to() { return v; }
	long long  either() { return u; }
	long long other() { return v; }
	long long weight() { return wt; }
	bool operator==(edge_t other) { return u == other.u and v == other.v; }
	bool operator<(edge_t other) { return  wt < other.wt; }
};










int main() {
	
	int t;
	cin >> t;
	while(t--) {
		undirected_graph<long long, edge_t> g;
		long long n, m, u, v, wt;
		cin >> n >> m;
		while(m--) {
			cin >> u >> v >> wt;
			edge_t e(u, v, wt);
			g.add_edge(e);
		}
	
		cin >> n >> m;
		dijkstra_sssp<undirected_graph<long long, edge_t>> shpath(g, n);
		long long len = shpath.dist_to(m);
		if(len != -1)
			cout << len << endl;
		else
			cout << "NO" << endl;
	}
}

/*

concept graph {
	Iterators
	
	vbegin();
	vend();
	ebegin();
	eend();
	avbegin(vertex);
	avend();
	aebegin(vertex);
	aeend(vertex);
	
	Interface
	add_edge
	add_vertex
};

*/
