#include <bits/stdc++.h>
#include <alglib/graph/directed_graph.h>
#include <alglib/graph/dfs.h>

using namespace std;
using namespace alglib::graph;

int main() {
    directed_graph<int> g;

    vector<int> numbers = {2, 3, 5, 6, 7, 8, 10, 12};
    
    for(int nu : numbers)
        g.add_vertex(nu);

    // create an edge (a, b) if a | b for all pairs
    for(int i = 0; i < numbers.size(); i++)
        for(int j = i+1; j < numbers.size(); j++)
            if(numbers[j] % numbers[i] == 0)
                g.add_edge(numbers[i], numbers[j]);

    vector<int> dfs;
    preorder_dfs(g, back_inserter(dfs));

    for(int no : dfs)
        cout << no << "\t";
    cout << endl;
}
