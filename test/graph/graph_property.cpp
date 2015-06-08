#include <alglib/graph/directed_graph.h>
#include <alglib/graph/graph_property.h>
#include <bits/stdc++.h>

using namespace std;
using namespace alglib::graph;

int main() {

    typedef directed_graph<string> GraphT;
    
    // A social network of people
    GraphT graph;

    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");

    // Property on each vertex: let us say the age of each person
    vertex_property<GraphT, int> P(graph);

    P["A"] = 10;
    P["B"] = 20;
    P["C"] = 30;
    P["D"] = 40;
    //! P["E"] = 50; // Causes exception to be thrown

    for(auto it = graph.vbegin(); it != graph.vend(); it++)
        cout << "Age of person: " << *it << " is: " << P(*it) << endl;



}
