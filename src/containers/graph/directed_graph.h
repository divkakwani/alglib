
#ifndef _DIRECTED_GRAPH_H
#define _DIRECTED_GRAPH_H


template<typename vertex_t, typename edge_t>
class directed_graph : public graph<vertex_t, edge_t> {

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

    void add_vertex(const vertex_t& v);
    void add_edge(const edge_t& e);

    int vsize();
    int esize();

    int indeg(const vertex_t& v) const;
    int outdeg(const vertex_t& v) const;

    // Iterators
    typedef vector<vertex_t>::const_iterator const_viterator;
    typedef vector<edge_t>::const_iterator const_eiterator;


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

    // Indices
    map<vertex_t, int> vindex;
    map<int, vertex_t> vinv_index;
    map<edge_t, int> eindex;
    map<



    // Adjaceny list
    vector<vector<pair<int, int>>> adj_list;

    /* complexity requirement
      add vertices - check if it's not already there
                      then insert

      add edge - check if it's not there

    */

};



template<typename vertex_t, typename edge_t>
directed_graph<vertex_t, edge_t>::directed_graph() {

}

template<typename vertex_t, typename edge_t>
directed_graph<vertex_t, edge_t>::~directed_graph() {

}

template<typename vertex_t, typename edge_t>
void directed_graph<vertex_t, edge_t>::add_vertex(const vertex_t& v) {

  if(index.find(v) == index.end()) {
    index[v] = index.size();
    adj_list.push_back(vector<pair<int, int>>());
  }
}

void add_edge(const edge_t& e);

template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t>::vsize() {
  return vertices.size();
}

template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t>::esize() {
  return edges.size();
}

template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t>::indeg(const vertex_t& v) const {
  return
}

template<typename vertex_t, typename edge_t>
int directed_graph<vertex_t, edge_t>::outdeg(const vertex_t& v) const {
  for(auto& adj : adj_list) {
    for(auto&)
  }
}





/*


struct hasher {

int operator()(const vertex_t& v) const {
char* mem = static_cast<char*>(&v);
int hashval = 0;
for(int i = 0; i < sizeof(v); i++) {
hashval += mem;
}
return hashval;
}
};


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
