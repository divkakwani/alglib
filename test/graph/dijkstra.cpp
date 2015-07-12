
#include <alglib/graph/directed_graph.h>
#include <alglib/graph/shortest_path/dijkstra.h>

using namespace std;
using namespace alglib::graph;


int main() {

    using graph_type = directed_graph<int, int>;

    // vertex_type = int; edge_attribute_type = int = weight
    directed_graph<int, int> G;

    for(int i = 0; i < 10; i++)
        G.add_vertex(i);

    G.add_edge(1, 3, 4);
    G.add_edge(3, 5, 6);
    G.add_edge(1, 5, 7);

    dijkstra<graph_type> dijk (G, 1);

    cout << dijk.shortest_dist_to (5) << endl;

    vector<int> path;

    dijk.shortest_path_to (5, back_inserter (path));
    
    cout << "Shortest path is: \n";
    for (int v : path)
        cout << v << "\t";
    cout << endl;
}
