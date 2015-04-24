
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

  protected:

    /*

         +--------+
         |Key: Val|
         |List    |
         +---+----+
             |
    +---+----+---+---+
    |   |  Attr  |   |
    |   +--------+   |
    |   | vertex |   |
    +-|-+--------+-|-+
      |            |
      |            |
    +-v-+        +-v-+
    |IN |        |OUT|
    +---+        +---+



    */

    struct composite_vertex {
      map<string, attrval&> attributes;   // for decorating vertices
      set<composite_edge&> in;
      set<composite_edge&> out;
      vertex_t v;

    }

    struct composite_edge {
      map<string, attrval&> attributes;  // for decorating edges
      composite_vertex& u;
      composite_vertex& v;
      edge_t edge;
    }



    /* Main container - holds composite edge and vertex objects */

    set<composite_edge>    edge_list;
    set<composite_vertex>  vertex_list;


    /** Complexity Gurantees

        add_vertex    = O(log n)
        add_edge      = O(log n)
        remove_vertex = O(deg(v)log E)
        remove_edge   = O(log E)
        indeg         = O(log V)
        outdeg        = O(log V)
        num_vertices  = O(1)
        num_edges     = O(1)

        TODO: Improve indeg and outdeg.

    **/



    void add_vertex(const vertex_t& v) {

      // Synthesize a composite vertex and insert
      vertex_list.insert(composite_vertex(v));

    }

    void add_edge(const vertex_t& u, const vertex_t& v, edge_t e) {

      // Synthesize a composite edge
      composite_edge ce(u, v, e);
      auto ret = edge_list.insert(ce);

      // Make entries in the adjacency list
      auto it1 = vertex_list.find(u);
      auto it2 = vertex_list.find(v);

      (it1->out).insert(*(ret.first));
      (it2->in).insert(*(ret.first));


    }

    void remove_vertex(vertex_t v) {

      auto del_vertex = vertex_list.find(del_vertex);

      // Done in 2 parts
      // Part 1: For every outgoing edge (v, x):
      //         remove the edge's entry in the 'in' list of vertex x
      for(auto it = (del_vertex->out).begin(); it != (del_vertex->out).end(); it++) {
        (it->dest.in).erase(*it);
        edge_list.erase(*it);
      }

      // Part 2: For every incoming edge (x, v):
      //         Remove the entry of the edge in the 'out' list of vertex x
      //         delete the edge (x, v)
      for(auto it = (del_vertex->in).begin(); it != (del_vertex->in).end(); it++) {
        (it->origin.out).erase(*it);
        edge_list.erase(*it);
      }

      // Delete the vertex
      vertex_list.erase(del_vertex);

    }

    void remove_edge(edge_t e) {

      auto it = edge_list.find(e);
      it->orgin.out.erase(*it);
      it->dest.in.erase(*it);
      edge_list.erase(it);

    }


    int indeg(vertex_t v) {
      auto it = vertex_list.find(v);
      if(it != vertex_list.end())
        return it->out.size();
      return -1;
    }

    int outdeg(vertex_t v) {
      auto it = vertex_list.find(v);
      if(it != vertex_list.end())
        return it->in.size();
      return -1;
    }

    int num_vertices() const { return vertex_list.size(); }
    int num_edges() const { return edge_list.size(); }


    auto vbegin() {
      return vertex_list.begin();
    }

    auto vend() {
      return vertex_list.end();
    }


};



template<typename vertex_t, typename edge_t>
directed_graph<vertex_t, edge_t>::directed_graph() {
  // empty
}

template<typename vertex_t, typename edge_t>
directed_graph<vertex_t, edge_t>::~directed_graph() {
  // empty
}


/* Obsolete

template<typename vertex_t, typename edge_t>
void directed_graph<vertex_t, edge_t>::add_vertex(const vertex_t& v) override {

  if(vertices.find(v) == vertices.end()) {
    auto it = vertices.find(v);
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

*/
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
