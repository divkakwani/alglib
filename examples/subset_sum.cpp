#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <iterator>

using namespace std;

void find_sum(vector<int>& assign, int sum, int done, int i, vector<int>& vec, int M, vector<vector<int>>& good_tpls) {	

	if(sum > M || i > vec.size())
		return;		// Prune search

	if(sum == M) {
		good_tpls.push_back(vector<int>(assign.begin(), assign.begin() + done));
		return;
	}
		
	assign[done] = vec[i];
	find_sum(assign, sum + vec[i], done + 1, i + 1, vec, M, good_tpls);

	find_sum(assign, sum, done, i + 1, vec, M, good_tpls);	// Do not include the ith elt.

}

void subset_sum(vector<int>& vec, int M, vector<vector<int>>& good_tpls) {

	vector<int> assign(vec);
	find_sum(assign, 0, 0, 0, vec, M, good_tpls);
}

int main() {
	vector<vector<int>> good_tpls;
	vector<int> vec{2, 4, 1, 3, 6, 5};
	const int sz = 100, m = 6;
	subset_sum(vec, m, good_tpls);
	
	cout << "Answers\n";
	for(auto& good_tpl : good_tpls) {
		for(int x : good_tpl)
			cout << x << "\t";
		cout << endl;
	}

}
