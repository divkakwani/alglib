
#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
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

    template<typename pvertex_type>
    std::set<pvertex_type>& get_vertices() const;

    template<typename pedge_type>
    std::set<pedge_type> get_edges() const;

    void add_vertex(Vertex* v);
    void add_edge(Edge* e);

    template<typename pvertex_type>
    std::vector<pvertex_type> adjTo(Vertex* v);


};

UndirectedGraph::UndirectedGraph() {
  total_vertices = 0;
}

template<typename pvertex_type>
std::set<pvertex_type>& UndirectedGraph::get_vertices() const {

  std::set<pvertex_type>* pvertices = new std::set<pvertex_type>();
  for(auto& vertex : vertices)
    pvertices->insert(dynamic_cast<pvertex_type>(vertex));

  return *pvertices;
}

template<typename pedge_type>
std::set<pedge_type> UndirectedGraph::get_edges() const {

  std::set<pedge_type>* pedges = new std::set<pedge_type>();
  for(auto& edge : edges )
    pedges->insert(dynamic_cast<pedge_type>(edge));

  return *pedges;

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

template<typename pvertex_type>
std::vector<pvertex_type> UndirectedGraph::adjTo(Vertex* v) {

  std::vector<pvertex_type> adjacent;

  if(adj_list.find(v) == adj_list.end())
    throw "Invalid Vertex";

  for(auto& vertex : adj_list[v]) {
    adjacent.push_back(dynamic_cast<pvertex_type>(vertex));
  }

  return adjacent;
}




#endif
