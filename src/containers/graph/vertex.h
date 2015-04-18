
#ifndef _VERTEX_H
#define _VERTEX_H

/*
The vertex class provides the interface that the UndirectedGraph class requires.
An UndirectedGraph object can hold user-defined vertex_types if they are derived
from the Vertex class
*/
class vertex {
  public:
    virtual size_t hash_code() = 0;
    virtual bool operator<(Vertex* v) = 0;
    virtual bool operator>(Vertex* v) = 0;
    virtual bool operator==(Vertex* v) = 0;
};


#endif
