
## Graph Classes in alglib

A graph class is instantiated with a vertex type and an attribute type as follows:

```
graph_type_template<vertex_type, edge_attribute_type>
```
When no edge attribute is required, as in the case of an unweighted graph, it can be elided or set to void. 


The edges in the graph class are restriced to the form:

    E = (from, to, attr),      from and to are vertices and attr is the attribute.

Any customization of the edge can be performed by customizing the attribute field, which is why it is a template parameter:

```
template<typename vertex_t, typename attr_t>
struct edge_t;
```

The above scheme does not permit user-defined edge types; the edge types must be the ones instantiated through the above template class. The reason for using this
scheme is that it enforces the two fields: from and to in every edge class. Since the two fields are necessary anyway, this scheme makes the library design easy by 
avoiding extra code to enforce these two fields, should user-defined types be allowed.

The user also has an option to change the internal representation of the graph by specifying so in an optional template parameter, model. Two models are provided by
alglb, adj_list and adj_matrix. The user can also use his own model as well, so long as they adhere to the interface established by the graph_model class.

To sum up, the above design of the graph classes allows the users to:
* Use _any_ type as the vertex_type.
* Attach any type of attribute with each of the edges.
* Change between internal representations of the graph.


#### Inspection

The graph classes provide iterators for the inspection of vertices and edges. There are four type of iterators:
* vertex iterator
* edge iterator
* adjacency vertex iterator
* adjacency edge iterator

All of them are constant, and for a good reason too. If they were allowed to be non-const, any change in a vertex or edge unbeknownst to the graph class can create 
inconsistencies in the whole data structure.

#### Resource Ownership

All the graph classes create their own copy of vertices and edges. They are the owner of these copies. Further, these copies are only modifiable by the graph classes
themselves. Hence, any iterator to vertices or edges are always constant.

As a consquence of having private copies, the graph classes can have a big memory footprint. On the flip-side, if the graph classes do not create their own copies, it can
in no way ensure the vertices remain constant.

For better efficiency, the addition of move-semantics and eliding copying for const- vertices is under consideration.



### Algorithms on the Graph Classes


The graph classes themselves do not offer much for the algorithms, except the iterators. All the algorithms visit the graph via these iterators and all this while the graph classes
themselves remain inert.

There is also one more useful concept that alglib provides - graph_property, through two classes - vertex_property and edge_property. They are so central to the design of alglib that
a number of algorithms make use of property objects to store the results of their computation. For instance, the connected_component function returns a property object that assigns
each vertex a component id.

With this framework, let us see how some of the common graph algorithms are implemented by alglib:

* DFS and BFS

    These functions return a permutation of the vertex set as specified by the dfs/bfs algorithm. They do so by copying the permutation in a destination container, the iterator
    to which they receive as an argument.

* Shortest path algorithms

    All shortest path algorithms require a functor, Cost, to be supplied as a template argument. This functor extracts cost given an edge and is used by the algorithms to evaluate
    path costs. The return value is `vertex_property` object carrying shortest-path cost against each vertex.

* MST algorithms

    This operation extracts a subgraph from a given graph. The details of operating on subgraph is given in the next section. An alternative way would be to return an edge_property
    with a boolean value assigned to each edge indicating its presence or absence in the MST.

* Eccentricity
    
    Similar to ssp, this function also returns a `vertex_property` object with each vertex assigned the cost of the path to the most distant vertex from it.



#### Subgraphs




