
#include <alglib/graph/directed_graph.h>
#include <alglib/graph/dijkstra.h>

using namespace std;
using namespace alglib::graph;


int main() {

    // vertex_type = int; edge_attribute_type = int = weight
    directed_graph<int, int> G;

    for(int i = 0; i < 10; i++)
        G.add_vertex(i);

    G.add_edge(1, 3, 4);
    G.add_edge(3, 5, 6);
    G.add_edge(1, 5, 7);

    vertex_property<directed_graph<int, int>, int> D = dijkstra(G, 1);
   
    cout << D;

}
