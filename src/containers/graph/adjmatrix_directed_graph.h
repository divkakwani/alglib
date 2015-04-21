

#ifndef _ADJMATRIX_DIRECTED_GRAPH_H
#define _ADJMATRIX_DIRECTED_GRAPH_H


template<typename vertex_t, typename edge_t>
class adjmatrix_directed_graph : public graph<vertex_t, edge_t> {

  public:

    class const_viterator;
    class const_eiterator;


  private:

    bool** adjmatrix;

    map<pair<vertex_t, vertex_t>, pair<bool, edge_t>

};

template<typename vertex_t, typename edge_t>
void adjmatrix_directed_graph :: add_edge(edge_t& e) {

}


#endif
