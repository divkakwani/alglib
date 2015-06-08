#include <iostream>
#include <vector>
#include <alglib/graph/directed_graph.h>

using namespace std;
using namespace alglib::graph;

int main() {

    directed_graph<string, int> G;

    string c1 = "Bikaner";
    string c2 = "Bangalore";
    string c3 = "Jaipur";
    string c4 = "Hanumangarh";
    string c5 = "Jodhpur";


    G.add_vertex(c2);
    G.add_vertex(c1);
    G.add_vertex(c3);
    G.add_vertex(c4);
    G.add_vertex(c5);

    G.add_edge(c1, c2, 100);
    G.add_edge(c5, c1, 250);
    G.add_edge(c2, c3, 110);
    G.add_edge(c1, c4, 40);
   
    cout << "\nAll the cities: ";
    for(auto it = G.vbegin(); it != G.vend(); it++)
        cout << *it << "\t";
    cout << endl;
    
    cout << "\nCities adjacent to Bikaner: ";
    for(auto it = G.avbegin(c1); it != G.avend(c1); it++)
        cout << *it << "\t";

    cout << endl;

    cout << "\n\nDirected graph with unweighted edges:\n";
    // unweighted (or graph with unattributed edges) graph
    directed_graph<int> G1;
    G1.add_vertex(3);
    G1.add_vertex(10);

    G1.add_edge(3, 10); // OK
    // G1.add_edge(3, 10, 10);  // Error
    
    cout << "\nAll the vertices: ";
    for(auto it = G1.vbegin(); it != G1.vend(); it++)
        cout << *it << "\t";
    cout << endl;
}
