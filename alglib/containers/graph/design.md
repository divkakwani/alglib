
# Design of the Graph Library




### Established tenets

* An `undirected_graph` _is_ a `directed_graph`.
* Provide several types of iterators to iterate over the graph.
* Provide nested types for outsiders to work with it.
* _Ownership_ : The graph creates a copy of the vertices and edges object edges that are passed to it. It becomes the sole owner of those copies. Cleaning up is, thus, the responsibility of the graph class.
* Handling big objects:

### Design Patterns Used
* _Iterator Pattern_ <br>
__Intent__: To traverse vertices/edges of a graph. There are four types of iterators: vertex iterator, edge iterator plus their constant versions. The iterators either traverse the entire graph or only vertices/edges adjacent to a vertex. These iterator types and their interfaces remain the same across all the graphs and thus can be used to write generic algorithms.

* _Decorator Pattern_ <br>
__Intent__:

## Graph API

#### Undirected Graph

```
// vertex opertions
add_vertex (const vertex& v);
delete_vertex (const vertex& v);

// edge operations
add_edge (const vertex_t& u, const vertex_t& v);
add_edge (const edge_t<vertex_t, attr_t>& edge);
delete_edge (const vertex_t u, const vertex_t v);
delete_edge (const edge_t<vertex_t, attr_t>& edge);
get_attr (const vertex_t& u, const vertex_t& v);

// Iterators
// vertex, edge and adjacency iterators.
```



## Graph Classes Hierarchy


## Vertices and Edges
### Vertex
It is a user-defined class with only requirement that it be `LessThanComparable`.

### Edge
It is also a user-defined class and thus can have any composition. However, there are few requirements that the graph classes and the algorithms on it place on the `edge` class.
For instance, dijkstra's algorithm requires:
```
concept edge {
	vertex& from();
	vertex& to();
	LessThanComparable& weight();
};
```

An edge class can have a richer interface, only that it must support the above interface.


## Design Choices

### Directed vs Undirected Graphs




### Weighted vs Unweighted Graphs

* `weight`, among other things, is a property of an edge. The graph classes need not care about it. Only the algorithms on weighted graph require `weight` as a property of an edge.

__How do we make algorithms that operate both on weighted and unweighted graph?__
<br>
An algorithm on a weighted graph always requires wieghts associated with edges. When considering an unweighted graph, it is an implicit assumption that all the weights are 1 unit.
Hence, we require an automatic conversion of an unweighted graph to a weighted graph with every edge weighted by 1 unit. The `unwted_to_wted` function does this.



### Adjaceny List vs Adjacency Matrix
The graph classes, for now, support only the adjaceny list implementation. In case it is required, one can simply inherit from the `graph` interface and create his own implemenation.<br>
An alternative strategy is to synthesize adjacency matrix of given graph object at the time of its usage.

## Creating Other Graph Types
