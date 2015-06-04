#include <iostream>
#include <vector>
#include <alglib/graph/undirected_graph.h>

using namespace std;

int main() {

    undirected_graph<string, int> G;

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
    
    cout << "Cities adjacent to Bikaner: ";
    for(auto it = G.avbegin(c1); it != G.avend(c1); it++)
        cout << *it << "\t";
    cout << endl;


    undirected_graph<int> G1;

    G1.add_vertex(2);
    G1.add_vertex(10);
    G1.add_vertex(11);
    G1.add_vertex(6);

    G1.add_edge(3, 10);
    G1.add_edge(10, 11);
    G1.add_edge(6, 10);

    cout << "Numbers adjacent to 10: ";
    for(auto it = G1.avbegin(10); it != G1.avend(10); it++) 
        cout << *it << "\t";
    cout << endl;
}
