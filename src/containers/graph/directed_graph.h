



template<typename vertex_t, typename edge_t>
class directed_graph {

  public:

    void add_vertex(const vertex_t& v);
    void add_edge(const edge_t& e);
    int indeg(const vertex_t& v) const;
    int outdeg(const vertex_t& v) const = 0;

    class const_viterator;
    class const_eiterator;

    // Iterators

    const_viterator vbegin();
    const_viterator vend();
    const_eiterator ebegin();
    const_eiterator eend();
    const_viterator avbegin(const vertex_t& v);
    const_viterator avend(const vertex_t& v);
    const_eiterator aebegin(const vertex_t& v);
    const_eiterator aeend(const vertex_t& v);



};
