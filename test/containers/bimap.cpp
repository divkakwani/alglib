
#include "../../src/containers/bimap.h"
#include <string>
#include <iostream>

using namespace std;

int main() {

  bimap<string, int> bm;

  bm.insert("div", 1);
  bm.insert("dip", 2);

  cout << bm.getimage("div") << endl;
  cout << bm.getimage("dip") << endl;
  cout << bm.getpreimage(1) << endl;
  cout << bm.getpreimage(2) << endl;

  // Iterator tests
  cout << "First type's set\n";
  for(auto it = bm.type1begin(); it != bm.type1end(); ++it)
    cout << *it << endl;

  cout << "Second type's set\n";
  for(auto it = bm.type2begin(); it != bm.type2end(); ++it)
    cout << *it << endl;

  cout << endl;



  return 0;
}
