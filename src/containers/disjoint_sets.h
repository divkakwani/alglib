#include <iostream>
#include <map>

using namespace std;
/*
	Operations on a disjoint set data structure
		union
		find_set
		make_set
		
*/


template<typename elt_type>
class disjoint_sets {
	
	private:
		map<int, int> parent;

		/* Translate to int */
		map<elt_type, int> eltid;
		map<int, elt_type> inv_eltid;

		int elts;

	public:
		disjoint_sets() : elts(0) {}
		void unite(elt_type e1, elt_type e2);
		int find_set(elt_type e);
		void make_set(elt_type e);
};

template<typename elt_type>
void disjoint_sets<elt_type>::make_set(elt_type e) {

	inv_eltid[elts] = e;
	eltid[e] = elts;
	parent[elts] = elts;
	++elts;
	
}

template<typename elt_type>
int disjoint_sets<elt_type>::find_set(elt_type e) {
	int id = eltid[e];
	while(id != parent[id])
		id = parent[id];
	return id;
}

template<typename elt_type>
void disjoint_sets<elt_type>::unite(elt_type e1, elt_type e2) {
	int repr_id1 = find_set(e1);
	int repr_id2 = find_set(e2);
	parent[repr_id1] = repr_id2;
}


int main() {
	disjoint_sets<int> sets;
	sets.make_set(32);
	sets.make_set(221);
	sets.unite(32, 221);
	cout << sets.find_set(32) << endl;
	cout << sets.find_set(221) << endl;
}

