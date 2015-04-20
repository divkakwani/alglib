
#ifndef _GRAPH_H
#define _GRAPH_H

/*
 * An abstract graph class. This class sits atop the graph class hierarchy.

*/

template<typename vertex_t, typename edge_t>
class graph {

  public:
    virtual void add_vertex(const vertex_t& v) = 0;
    virtual void add_edge(const vertex_t& u, const vertex_t& v) = 0;
    virtual void add_edge(const edge_t& e) = 0;

    virtual int vsize() const = 0;
    virtual int esize() const = 0;

    virtual int indeg(const vertex_t& v) const = 0;
    virtual int outdeg(const vertex_t& v) const = 0;

    class const_viterator;
    class const_eiterator;

    // Iterators
    virtual const_viterator vbegin() = 0;
    virtual const_viterator vend() = 0;
    virtual const_eiterator ebegin() = 0;
    virtual const_eiterator eend() = 0;
    virtual const_viterator avbegin(const vertex_t& v) = 0;
    virtual const_viterator avend(const vertex_t& v) = 0;
    virtual const_eiterator aebegin(const vertex_t& v) = 0;
    virtual const_eiterator aeend(const vertex_t& v) = 0;

};

template<typename vertex_t, typename edge_t>
class graph<vertex_t, edge_t> :: const_viterator {

  public:
    virtual const vertex_t& operator*() const = 0;
    virtual const veretx_t& operator++() const = 0;

};



template<typename vertex_t, typename edge_t>
class graph<vertex_t, edge_t> :: const_viterator {

  public:
    virtual const edge_t& operator*() const = 0;
    virtual const edge_t& operator++() const = 0;
    
};




#endif
