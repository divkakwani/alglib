#include <alglib/containers/graph/adj_list.h>
#include <alglib/containers/graph/edge.h>
#include <iostream>

using namespace std;


int main() {

    adj_list<int, edge_t<int>> al;

    edge_t<int> e;
    e.from = 3, e.to = 3, e.attribute = 100;

    al.add_vertex(4);
    al.add_vertex(3);
    al.add_edge(e);

    for(auto it = al.vbegin(); it != al.vend(); it++)
        cout << *it << endl;

}
