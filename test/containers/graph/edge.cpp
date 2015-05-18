#include <alglib/containers/graph/edge.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    
    // weighted edge
    edge_t<int, int> e;
    e.from = 2, e.to = 5, e.attribute = 1000;
    cout << "From:" << e.from << endl;
    cout << "To: " << e.to << endl;
    cout << "Attribute: " << e.attribute << endl;

    // unweighted edge
    edge_t<int> e1;
    e1.from = 4, e1.to = 3;
    cout << "From:" << e1.from << endl;
    cout << "To: " << e1.to << endl;

    using city = string;
    struct road { int len, toll, lanes; };

    edge_t<city, road> e2;
    e2.from = "bikaner", e2.to = "bangalore", e2.len = 1000, e2.toll = 100, e2.lanes = 4;
    cout << "From:" << e2.from << endl;
    cout << "To: " << e2.to << endl;
    cout << "Length: " << e2.len << endl;
    cout << "Lanes: " << e2.lanes << endl;

}
