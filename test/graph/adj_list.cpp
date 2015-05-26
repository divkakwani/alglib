#include <alglib/graph/adj_list.h>
#include <alglib/graph/edge.h>
#include <iostream>

using namespace std;


int main() {

    adj_list<int, edge_t<int>> al;
    
    edge_t<int> e;
    e.from = 3, e.to = 4, e.attribute = 100;
    edge_t<int> e1;
    e1.from = 10; e1.to = 3; e.attribute = 1000;

    al.add_vertex(4);
    al.add_vertex(3);
    al.add_vertex(10);
    al.add_edge(e);
    al.add_edge(e1);

    cout << "All the vertices: ";
    for(auto it = al.vbegin(); it != al.vend(); it++)
        cout << *it << "\t";

    cout << endl;

    cout << "Vertices adjacent to 10: ";
    for(auto it = al.avbegin(10); it != al.avend(10); it++)
        cout << *it << "\t";
    cout << endl;

    cout << "All the edges: ";
    
    for(auto it = al.ebegin(); it != al.eend(); ++it)
        cout << *it << "\t";

    cout << endl;

}
