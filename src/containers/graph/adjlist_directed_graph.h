
#ifndef _DIRECTED_GRAPH_H
#define _DIRECTED_GRAPH_H

#include <map>
#include <set>

template<typename vertex_t, typename edge_t>
class adjlist_directed_graph : public graph<vertex_t, edge_t> {

  public:

    /* Nested types */
    typedef vertex_t vertex_type;
    typedef edge_t edge_type;

    /* Ctors */
    directed_graph();
    /* L8R
    directed_graph(const set<vertex_t>& V);
    directed_graph(const set<vertex_t>& V, const set<edge_t>& E);
    */

    /* dtors */
    ~directed_graph();

    // Iterators
    class const_viterator;
    class const_eiterator;


    // Iterator returning methods
    const_viterator vbegin();
    const_viterator vend();
    const_eiterator ebegin();
    const_eiterator eend();
    const_viterator avbegin(const vertex_t& v);
    const_viterator avend(const vertex_t& v);
    const_eiterator aebegin(const vertex_t& v);
    const_eiterator aeend(const vertex_t& v);

  private:



    std::map<vertex_t, std::set<std::pair<vertex_t, edge_t>>> adjlist;
    int vertices;
    int edges;

};



template<typename vertex_t, typename edge_t>
directed_graph<vertex_t, edge_t>::directed_graph() {
  vertices = 0;
  edges = 0;

}

template<typename vertex_t, typename edge_t>
directed_graph<vertex_t, edge_t>::~directed_graph() {
    // empty
}

template<typename vertex_t, typename edge_t>
void directed_graph<vertex_t, edge_t>::add_vertex(const vertex_t& v) override {

  if(adjlist.find(v) == adjlist.end()) {
    adjlist[v]= set<pair<vertex_t, edge_t>>();
    vertices++;
  }
}

template<typename vertex_t, typename edge_t>
void directed_graph<vertex_t, edge_t> :: add_edge(const edge_t& e) override {

  if(adjlist.find(e.from) != adjlist.end()) {
    if(adjlist[e.from].find(e.to) != adjlist[e.from].end()) {
       adjlist[e.from].insert(e.to);
       edges++;
    }
  }
}

template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t> :: vsize() const override {
  return vertices;
}

template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t> :: esize() const override {
  return edges;
}

template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t> :: indeg(const vertex_t& v) const override {

  int count = 0;
  for(auto it = adjlist.begin(); it != adjlist.end(); it++) {
    for(auto it2 = it->begin(); it2 != it->end(); it2++) {
      if(it2->first == v)
        count++;
    }
  }
  return count;

}


template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t> :: outdeg(const vertex_t& v) const override {

  if(adjlist.find(v) != adjlist.end())
    return adjlist[v].size();

  return 0; // Throw error or return 0 since the vertex doesn't exist
}

template<typename vertex_t, typename edge_t>
const_viterator directed_graph<vertex_t, edge_t> :: vbegin() {


}


  /*


template<typename vertex_t, typename edge_t>
class directed_graph<vertex_t, edge_t> :: const_viterator :
public std::iterator<std::output_iterator_tag, vertex_t> {


public:

const vertex_t& operator*() {
if(idx >= vertices.size() or idx < 0)
throw "out of bounds";
return vertices[idx];
}
const_viterator operator++() {
if(idx + 1 == vertices.size()) {
throw "out of bounds";
}
++idx;
return vertices[idx - 1];
}
bool operator==(const const_viterator& it) const {
return idx == it.idx;
}
bool operator==(const const_viterator& it) const {
return idx != it.idx;
}

private:
int idx = 0;

};
*/



#endif
