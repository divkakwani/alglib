#include <iostream>
#include <alglib/graph/directed_graph.h>

using namespace std;

int main() {

    directed_graph<string, int> G;

    string c1 = "Bikaner";
    string c2 = "Bangalore";
    string c3 = "Jaipur";
    string c4 = "Hanumangarh";
    string c5 = "Jodhpur";


    G.add_vertex(c1);
    G.add_vertex(c2);
    G.add_vertex(c3);
    G.add_vertex(c4);
    G.add_vertex(c5);

    G.add_edge(c1, c2, 100);
    G.add_edge(c5, c1, 250);


//    for(auto it = G.alists.begin(); it != G.alists.end(); it++)
//        cout << it->first << endl;

    for(auto it = G.vbegin(); it != G.vend(); it++)
        cout << *it << endl;
};
