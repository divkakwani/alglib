
## Design of the Graph Library

#### Design issues
* Allow a graph to change implementation between adjacency matrix, adjacency list and something else.


#### Established tenets

* An `undirected_graph` _is_ a `directed_graph`.
* Provide several types of iterators to iterate over the graph.
* Provide nested types for outsiders to work with it.
* _Ownership_ : The graph creates a copy of the vertices and edges object edges that are passed to it. It becomes the sole owner of those copies. Cleaning up is, thus, the responsibility of the graph class.
* Handling big objects:

#### Design Patterns Used
* _Iterator Pattern_ <br>
__Intent__: To traverse vertices/edges of a graph. There are four types of iterators: vertex iterator, edge iterator plus their constant versions. The iterators either traverse the entire graph or only vertices/edges adjacent to a vertex. These iterator types and their interfaces remain the same across all the graphs and thus can be used to write generic algorithms.

* _Decorator Pattern_ <br>
__Intent__: 



## Concept
