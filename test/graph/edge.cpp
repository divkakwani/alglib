#include <alglib/graph/edge.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    
    // weighted edge
    edge_t<int, int> e(2, 5, 1000);
    cout << e << endl;

    // unweighted edge
    edge_t<int> e1(4, 3);
    cout << e1 << endl;

    struct road { int length; int lanes; };
    using city = string;

    // custom edge
    edge_t<city, road> e2("Bikaner", "Jodhpur", road {10, 4});
    cout << e2.from << ", " << e2.to << ", "
         << e2.attribute.length << endl;
}
