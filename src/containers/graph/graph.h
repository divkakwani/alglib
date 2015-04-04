
#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include "vertex.h"
#include "edge.h"

// an abstract graph class
// The class can be used with any vertex and edge types inherited from the
// Vertex and the Edge class respectively.

class graph {

  public:

  	struct Hasher {
  		std::size_t operator()(Vertex* const& key) const{
        	return key->hash_code();
      	}
    };

    virtual int no_of_vertices() const = 0;

    /* typedefs */
    typedef

    /* Iterators */
    class iterator : public std::iterator<std:: {

    };




    template<typename OutputIterator>
    virtual OutputIterator get_vertices(OutputIterator dest) const = 0;

    template<typename OutputIterator>
    virtual OutputIterator get_edges(OutputIterator dest) const = 0;

    virtual void add_vertex(Vertex* v) const = 0;
    virtual void add_edge(Edge* e) = 0;

    template<typename OutputIterator>
    virtual OutputIterator adjTo(Vertex* v, OutputIterator dest) const = 0;

    virtual int indeg(Vertex* v) const = 0;
    virtual int outdeg(Vertex* v) const = 0;


};


#endif
