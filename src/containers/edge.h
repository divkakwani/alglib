
#ifndef _EDGE_H
#define _EDGE_H

#include "vertex.h"

class Edge {
  public:
    virtual int hash_code() = 0;
    virtual Vertex* initial_vertex() = 0;
    virtual Vertex* terminal_vertex() = 0;
};

#endif
