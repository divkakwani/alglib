#include <alglib/graph/adj_list.h>
#include <alglib/graph/edge.h>
#include <iostream>

using namespace std;


int main() {

    adj_list<string, edge_t<string, int>> al;
    
    string c1 = "deharadun",
           c2 = "rishikesh",
           c3 = "kulu manali",
           c4 = "haridwar";

    edge_t<string, int> e1(c1, c2, 100);
    edge_t<string, int> e2(c3, c4, 200);

    al.add_vertex(c1);
    al.add_vertex(c2);
    al.add_vertex(c3);
    al.add_edge(e1);
    al.add_edge(e2);

    cout << "All the vertices: ";
    for(auto it = al.vbegin(); it != al.vend(); it++)
        cout << *it << "\t";

    cout << endl;

    cout << "Vertices adjacent to kulu manali: ";
    for(auto it = al.avbegin(c3); it != al.avend(c3); it++)
        cout << *it << "\t";
    cout << endl;

    cout << "All the edges: "; 
    for(auto it = al.ebegin(); it != al.eend(); ++it)
        cout << *it << "\t";

    cout << endl;

}
