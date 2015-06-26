
## Graph Classes in alglib

A graph class is instantiated with a vertex type and an attribute type as follows:

```
graph_type_template<vertex_type, edge_attribute_type>
```
When no edge attribute is required, as in the case of an unweighted graph, it can be set to void. 


The edges in the graph class are restriced to the form:
    E = (from, to, attr),  from and to are vertices and attr is the attribute.
Any customization of the edge can be performed by customizing the attribute field, which is why it is a template parameter:
```
template<typename vertex_t, typename attr_t>
struct edge_t;
```

The above scheme does not permit user-defined edge types; the edge types must be the ones instantiated through the above template class. The reason for using this
scheme is that it enforces the two fields: from and to in every edge class. Since the two fields are necessary anyway, this scheme makes the library design easy by 
avoiding extra code to enforce these two fields, should user-defined types be allowed.

The user also has an option to change the internal representation of the graph by specifying so in an optional template parameter, model. Two models are provided by
alglb, adj_list and adj_matrix. However, the graph classes can use other user-defined models as well, as long as they adhere to the interface established by the graph_model
class.

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
All of them are constant, and for a good reason too. If they were allowed to be non-const, any change in a vertex or edge, unbeknowst to the graph class, can create 
inconsistencies in the whole data structure.

#### Resource Ownership

All the graph classes create their own copy of vertices and edges. They are the owner of these copies. Further, these copies are only modifiable by the graph classes
themselves. Hence, any iterator to vertices or edges are always constant.
Consquentially, the graph classes can have a big memory footprint. On the flip-side, if the graph classes do not create their own copies, it can in no way ensure the vertices
remain constant. For better efficiency, move-semantics and eliding copying for const- vertices would soon be added.



### Algorithms on the Graph Classes


The graph classes themselves do not offer much for the algorithms, except the iterators. All the algorithms visit the graph via these iterators and all this while the graph classes
themselves remain inert.
There is also one more useful concept that alglib provides - graph_property, through two classes - vertex_property and edge_property. They are so central to the design of alglib that
a number of algorithms make use of property objects to store the results of their computation. For instance, the connected_component function returns a property object that assigns
each vertex a component id.

With this framework, let us see how some of the popular graph algorithms can be implemented:

* DFS and BFS
* Shortest path algorithms
* MST algorithms
* Eccentricity




