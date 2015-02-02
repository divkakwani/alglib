
#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include "vertex.h"
#include "edge.h"

// Undirected graph
// The class can be used with any vertex and edge types inherited from the
// Vertex and the Edge class respectively.

class UndirectedGraph {

    struct Hasher {
      std::size_t operator()(Vertex* const& key) const{
        return key->hash_code();
      }
    };
    int total_vertices;
    std::unordered_map<Vertex*, std::vector<Vertex*>, Hasher> adj_list;
    std::set<Vertex*> vertices;
    std::set<Edge*> edges;

  public:
    UndirectedGraph();

    int no_of_vertices() const;

    template<typename OutputIter>
    OutputIter get_vertices(OutputIter dest) const;

    template<typename OutputIter>
    OutputIter get_edges(OutputIter dest) const;

    void add_vertex(Vertex* v);
    void add_edge(Edge* e);

    template<typename OutputIter>
    OutputIter adjTo(Vertex* v, OutputIter dest);

    // Experimental
    // Iterator_type dfs_begin();
    // Iterator_type dfs_end();


};

UndirectedGraph::UndirectedGraph() {
  total_vertices = 0;
}

int UndirectedGraph::no_of_vertices() const {
  return total_vertices;
}

template<typename OutputIter>
OutputIter UndirectedGraph::get_vertices(OutputIter dest) const {

  typedef typename std::iterator_traits<OutputIter>::value_type val_type;

  for(auto& vertex : vertices)
    *dest++ = dynamic_cast<val_type>(vertex);

  return dest;
}

template<typename OutputIter>
OutputIter UndirectedGraph::get_edges(OutputIter dest) const {

  typedef typename std::iterator_traits<OutputIter>::value_type val_type;

  for(auto& edge : edges )
    *dest++ = dynamic_cast<val_type>(edge);

  return dest;

}

void UndirectedGraph::add_vertex(Vertex* v) {

  if(vertices.find(v) != vertices.end())
    throw "Duplicate ID";
  adj_list[v] = std::vector<Vertex*>();
  vertices.insert(v);
  total_vertices++;
}

void UndirectedGraph::add_edge(Edge* e) {

  Vertex* v1 = e->initial_vertex();
  Vertex* v2 = e->terminal_vertex();
  if(edges.find(e) != edges.end())
    throw "Duplicate";
  if(vertices.find(v1) == vertices.end())
    add_vertex(v1);
  if(vertices.find(v2) == vertices.end())
    add_vertex(v2);

  adj_list[v1].push_back(v2);
  adj_list[v2].push_back(v1);

  edges.insert(e);
}

template<typename OutputIter>
OutputIter UndirectedGraph::adjTo(Vertex* v, OutputIter dest) {

  typedef typename std::iterator_traits<OutputIter>::value_type val_type;

  if(adj_list.find(v) == adj_list.end())
    throw "Invalid Vertex";

  for(auto& pvertex : adj_list[v]) {
    *dest++ = dynamic_cast<val_type>(pvertex);
  }

  return dest;
}




#endif
