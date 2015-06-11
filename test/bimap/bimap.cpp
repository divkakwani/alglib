
#include <alglib/bimap/bimap.h>
#include <string>
#include <iostream>

using namespace std;
using namespace alglib::bimap;

int main() {

  bimap<string, int> bm;

  bm.insert("div", 1);
  bm.insert("dip", 2);

  cout << bm.get_image("div") << endl;
  cout << bm.get_image("dip") << endl;
  cout << bm.get_preimage(1) << endl;
  cout << bm.get_preimage(2) << endl;

  // Iterator tests
  cout << "Domain:  \t";
  for(auto it = bm.domain_begin(); it != bm.domain_end(); ++it)
    cout << *it << "\t";

  cout << endl;

  cout << "Codomain:\t";
  for(auto it = bm.codomain_begin(); it != bm.codomain_end(); ++it)
    cout << *it << "\t";

  cout << endl;

  return 0;
}
