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
				vertex_t u = e.either(), v = e.other(u);
				add_vertex(u);
				add_vertex(v);
				adjacency_list[u].push_back(v);
				adjacency_list[v].push_back(u);
				adjacency_edge[u].push_back(e);
				adjacency_edge[v].push_back(e);
				edge_list.push_back(e);
			}
		}

		long long vsize() const {
			return vertex_list.size();
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










template<typename vertex_t, typename edge_t, typename OutputIter>
OutputIter prim_mst(undirected_graph<vertex_t, edge_t>& G, OutputIter res) {

	/*
		Maintain a set of edges that go out of the tree
		In each iteration, pick the lightest of them and include it in T.
	*/
	set<edge_t> edges;
	set<vertex_t> T;

	vertex_t start = *G.vbegin();
	T.insert(start);
	for(auto it = G.aebegin(start); it != G.aeend(start); it++)		// Why seg-fault?
		edges.insert(*it);

	long long sz = G.vsize();
	while(T.size() != sz) {

		edge_t lightest = *edges.begin();
		edges.erase(*edges.begin());

		vertex_t u = lightest.either();
		vertex_t v = lightest.other(u);

		bool u_in_T = T.find(u) != T.end();
		bool v_in_T = T.find(v) != T.end();

		if(u_in_T and !v_in_T) {
			res++ = lightest;
			T.insert(v);
			for(auto it = G.aebegin(v); it != G.aeend(v); it++)
				edges.insert(*it);
		}
		if(!u_in_T and v_in_T) {
			res++ = lightest;
			T.insert(u);
			for(auto it = G.aebegin(v); it != G.aeend(v); it++)
				edges.insert(*it);
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
	long long other(long long vertex) { return vertex == u ? v : u; }
	bool operator==(const edge_t other) const { return u == other.u and v == other.v; }
	bool operator<(const edge_t other) const { return  wt < other.wt; }
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
	prim_mst(g, back_inserter(mst));

	long long cost = 0;
	for(edge_t edge : mst)
		cost += edge.wt;

	cout << cost << endl;
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
