

#include <iostream>
#include <alglib/containers/disjoint_sets.h>


int main() {
	disjoint_sets<int> sets;
	sets.make_set(32);
	sets.make_set(221);
	sets.make_set(311);
	sets.unite(32, 311);
	cout << sets.find_set(32) << endl;
	cout << sets.find_set(221) << endl;
}
