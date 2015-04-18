/****************

Travelling Salesman Problem 

****************/


#include <bits/stdc++.h>

using namespace std;
 
// Graph

const int v_sz = 5;

bool 	A[v_sz][v_sz];	// relation matrix
int 	W[v_sz][v_sz];

void init_graph() {
	memset(A, 0, sizeof(bool) * v_sz * v_sz);
	memset(W, 0x0F, sizeof(int) * v_sz * v_sz);
}

vector<int> adjacent(int vertex) {
	vector<int> vec;
	for(int v = 0; v < v_sz; v++)
		if(A[vertex][v])
			vec.push_back(v);
	return vec;
}

int lower_bound(vector<int>& path, int wt) {

	int lv = *path.rbegin();
	wt += *min_element(W[lv], W[lv] + v_sz);

	for(int v = 0; v < v_sz; v++)
		if(find(path.begin(), path.end(), v) == path.end())
			wt += *min_element(W[v], W[v] + v_sz);

	return wt;

}

int best = 100000;

void tsp_branch(vector<int>& path, int wt) {
	
	if(path.size() == v_sz) {
		int lv = *path.rbegin();
		if(A[lv][0]) {
			path.push_back(0);
			wt += W[lv][0];
			best = min(best, wt);
		}
		return;
	}

	int last_vertex = *path.rbegin();
	int lb = lower_bound(path, wt);

	if(lb >= best)
		return;

	for(int vertex : adjacent(last_vertex)) {
		if(find(path.begin(), path.end(), vertex) == path.end()) {
			vector<int> new_path = path;
			new_path.push_back(vertex);
			tsp_branch(new_path, wt + W[last_vertex][vertex]);
		}
	}
}

int main() {
	
	init_graph();

	// Textbook example

	for(int i = 0; i < v_sz; i++)
		for(int j = 0; j < v_sz; j++)
			if(i != j)
				A[i][j] = true;
	
	W[0][1] = 3;
	W[0][2] = 1;
	W[0][3] = 5; 
	W[0][4] = 8;
	W[1][0] = 3;
	W[1][2] = 6;
	W[1][3] = 7;
	W[1][4] = 9;
	W[2][0] = 1;
	W[2][1] = 6;
	W[2][3] = 4;
	W[2][4] = 2;
	W[3][0] = 5;
	W[3][1] = 7;
	W[3][2] = 4;
	W[3][4] = 3;
	W[4][0] = 8;
	W[4][1] = 9;
	W[4][2] = 2;
	W[4][3] = 3;
	
	vector<int> path;
	path.push_back(0);
	int wt = 0;
	tsp_branch(path, wt);
	
	cout << "Best: " << best << endl;




}
