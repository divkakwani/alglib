#include <iostream>
#include "../../src/containers/graph.h"
#include "../../src/containers/vertex.h"
#include "../../src/containers/edge.h"
#include <string>
#include <map>
#include "../../src/algorithms/graph_algo.h"
#include <unistd.h>
using namespace std;


class Person : public Vertex {
    string name;
  public:
    Person(string nam) {
      name = nam;
    }
    string get_name() {
      return name;
    }
    size_t hash_code() {
      hash<string> str_hash;
      return str_hash(name);
    }
    bool operator<(Vertex* v) {
      return this->hash_code() < v->hash_code();
    }
    bool operator>(Vertex* v) {
      return this->hash_code() > v->hash_code();
    }
    bool operator==(Vertex* v) {
      return this->hash_code() == v->hash_code();
    }

};

class Friendship : public Edge {
    Person* p1;
    Person* p2;
  public:
    Friendship(Person* p_1, Person* p_2) {
      p1 = p_1;
      p2 = p_2;
    }
    int hash_code() {
      return p1->hash_code() + p2->hash_code();
    }
    Vertex* initial_vertex() {
      return p1;
    }
    Vertex* terminal_vertex() {
      return p2;
    }
};

int main() {
  fsync(0);

  Person* p1 = new Person("Diptanshu");
  Person* p2 = new Person("Divyanshu");
  Person* p3 = new Person("Kumudini");
  Person* p4 = new Person("Geet");
  Person* p5 = new Person("Chitresh");

  Friendship* f1 = new Friendship(p1, p5);
  Friendship* f2 = new Friendship(p2, p3);
  Friendship* f3 = new Friendship(p1, p4);

  UndirectedGraph G;

  G.add_vertex(p1);
  G.add_vertex(p2);
  G.add_vertex(p3);
  G.add_vertex(p4);
  G.add_vertex(p5);

  G.add_edge(f1);
  G.add_edge(f2);
  G.add_edge(f3);

  vector<Person*> adj(10);
  auto last = G.adjTo(p2, adj.begin());

	cout << "Persons adjacent to Divyanshu\n";
  for(auto it = adj.begin(); it != last; it++)
    cout << (*it)->get_name() << endl;


  vector<Person*> dfs_traversal(10);

  auto lst = dfs_order(G, dfs_traversal.begin());

  cout << endl << "The dfs order is \n";

  for(auto it = dfs_traversal.begin(); it != lst; it++)
    cout << (*it)->get_name() << endl;
	

  vector<Person*> bfs_traversal(10);

  lst = bfs_order(G, bfs_traversal.begin());

  cout << endl << "The bfs order is \n";

  for(auto it = bfs_traversal.begin(); it != lst; it++)
    cout << (*it)->get_name() << endl;
	

  vector<Person*> topological_order(10);

  lst = topological_sort(G, topological_order.begin());

  cout << endl << "The topological order is \n";

  for(auto it = topological_order.begin(); it != lst; it++)
    cout << (*it)->get_name() << endl;
    
  /* 
  vector<pair<<Person*, int>> components(G.no_of_vertices());
  auto end = connected_components(G, components.begin());
  */
	
  cout << endl;
}
