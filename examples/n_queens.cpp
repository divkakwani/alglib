#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

// repr: config[i] stores the column no of a queen in ith row

template<typename Container>
bool is_safe(Container& config, int row, int col, int max_col) {
	/* Check if the placement of a queen on (row, col) respects prior placements. Two sufficient
	   conditions for it are:
	  	1. For every i < row, config[i] != col; i.e., no queen lies directly above the queen
		   in (row, col)
		2. The diagonals defined by (row, col) are (y - col) = +/-(x - row). Hence, for every
		   i < row, (config[i] - col) != +/-(i - row)
	*/
	bool safe = true;
	for(int i = 0; i < row; i++) {
		if(config[i] == col or abs(config[i] - col) == abs(i - row)) {
			   safe = false;
			   break;
		}
	}
	return safe;
}

template<typename Container, typename OPCont>
void nqueen(Container& config, int curr_row, int max_row, int max_col, OPCont& assignments) {
	
	if(curr_row == max_row) {
		// Safe assignment; store it
		vector<int> assign;
		copy_n(config.begin(), max_row, back_inserter(assign));
		assignments.push_back(assign);
	}
	
	// Try placing a queen on curr_row, starting from col 0 to max_col
	for(int col = 0; col < max_col; col++) {
	
		bool safe = is_safe(config, curr_row, col, max_col);
		if(safe) {
			config[curr_row] = col;
			nqueen(config, curr_row + 1, max_row, max_col, assignments);
		}
	}
	

}


int main() {
	const int max_col = 4, max_row = 4;
	vector<int> config(max_row, 0);
	vector<vector<int>> assignments;
	nqueen(config, 0, max_row, max_col, assignments);

	cout << "Safe assignments:\n";
	int n = 1;
	for(vector<int>& assignment : assignments) {
		cout << "Assignment no. " << n << endl;
		for(int col : assignment) {
			for(int i = 0; i < max_col; i++) {
				if(i != col)
					cout << 0 << "\t";
				else
					cout << 1 << "\t";
			}
			cout << endl;
		}
		++n;
	}
}
