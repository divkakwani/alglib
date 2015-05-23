
#include <iostream>
#include <queue>
#include <unordered_map>


using namespace std::queue;
using namespace std::cin, std::cout;


class dijkstra_sssp {

		graph& G;
		vertex& src;
		unordered_map<vertex, int> dist;
		
	public:
	
		dijkstra_sssp(graph& g, vertex& source);
		int dist_to(vertex& dest);

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


dijkstra::dijkstra_sssp(graph& g, vertex& source) : G(g), src(source) {

	const int inf = numeric_limits<int>::infinity();	// A constexpr - evaled at compile-time.
	
	// The set E stores our best estimate for the shortest path to each vertex.
	// The one with the least estimate is transferred to the set S and all the edges leaving it are relaxed
	set<pair<int, vertex>> E;	// ordered by distance

	for(auto it = G.vbegin(); it != G.vend(); it++) {
		dist[*it] = inf;
	}	
	
	dist[source] = 0;
	E.insert(make_pair(dist[source], source));
	
	while(!E.empty()) {
		pair<int, vertex> least = *E.begin();
		E.erase(*E.begin());
		
		int path_len = least.first;
		vertex u = least.second;
		
		// TODO : segregate relax procedure
		
		// relax all the outbound edges
		for(auto it = G.aebegin(u); it != G.aeend(u); it++) {
			vertex v = it->first;
			int wt = it->second;
			if(dist[u] + wt < dist[v]) {
				// Erase the earlier estimate
				E.erase(E.find(make_pair(v, dist[v])));
				
				dist[v] = dist[u] + wt;
				
				// Add the new estimate
				E.insert(make_pair(v, dist[v]));
			}
		}
	}	
	
}

int dijkstra_sssp::dist_to(vertex& dest) {
	return dist[dest];
}










