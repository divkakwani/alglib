#include <iostream>
#include "../../src/containers/graph.h"
#include "../../src/containers/vertex.h"
#include "../../src/containers/edge.h"
#include <string>
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

  UndirectedGraph G;

  G.add_vertex(p1);
  G.add_vertex(p2);
  G.add_vertex(p3);
  G.add_vertex(p4);
  G.add_vertex(p5);

  G.add_edge(f1);
  G.add_edge(f2);

  vector<Person*> adj = G.adjTo<Person*>(p2);
  for(auto& p : adj)
    cout << p->get_name() << endl;

  vector<Vertex*> dfs_traversal;
  dfs_traversal.reserve(100);


  dfs_order(G, back_inserter(dfs_traversal));
  cout << endl << "The dfs order is \n";
  for(auto& pvertex : dfs_traversal)
    cout << dynamic_cast<Person*>(pvertex)->get_name() << endl;

  cout << endl;
}
