
#ifndef _GRAPH_H
#define _GRAPH_H

#include <map>

// Undirected, static graph
class UndirectedGraph {
    const int v;
    map<Vertex, vector<Vertex>> adj_lst;
    // Should the edges be represented as a pair of vertices?
  public:
    UndirectedGraph();
    void addEdge(Vertex v1, Vertex v2);
    // Return an iterator to the graph
    vector<Vertex> adjTo(Vertex v); // or return an iterator to ?

};






#endif
