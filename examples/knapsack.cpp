#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

template<typename BidirectionalIter, typename OutputIter>
int knapsack01(BidirectionalIter in, int n, int capacity, OutputIter dest) {

	/*
		Value table
		
		        Capacity  --->
		      __0___1___2___3___4__..._cap_
		I  0  |___|___|___|___|___|___|___|
		T  1  |___|___|___|___|___|___|___|
		E  2  |___|___|___|___|___|___|___|
		M  .  |___|___|___|___|___|___|___|
		S  n-1|___|___|___|___|___|___|___|

	*/

	// Mem allocation
	int** values = new int*[n];
	for(int i = 0; i < n; i++) {
		values[i] = new int[capacity + 1](); 
	}
	
	int** keep = new int*[n];
	for(int i = 0; i < n; i++) {
		keep[i] = new int[capacity + 1](); 
	}
			

	for(int i = 0; i < n; i++) {
	
		// Get the item from input stream
		pair<int, int> item = *in;
		++in;
	
		for(int cap = 1; cap <= capacity; cap++) {
			
			/* Excluding the ith item:	
				If the item is not included, then the knapsack value is
				the value obtained by filling the knapsack optimally using
				the previous items
			*/
			int excluding_i= (i > 0) ? values[i - 1][cap] : 0;
			
			/* Including the ith item:
				If the item is included, then the optimal value is the item's value
				plus the value obtained by optimally filling the rest of the 
				knapsack.
			*/
			int including_i = 0;
			if(item.first <= cap) { including_i += item.second; }
			int left = cap - item.first;
			if(left > 0 and i > 0) { including_i += values[i-1][left]; }

			if(including_i > excluding_i) {
				values[i][cap] = including_i;
				keep[i][cap] = 1;
			}
			else {
				values[i][cap] = excluding_i;
				keep[i][cap] = 0;
			}
				
		}
	}
		
	int cap = capacity, item = n - 1;
	while(item >= 0) {
		--in;
		if(keep[item][cap]) {
			cap -= in->first;
			*dest++ = *in;
		}
		--item;
	}
	return values[n - 1][capacity];
}

int main() {

	vector<pair<int, int>> items, res;

	items.push_back(make_pair(4, 5));
	items.push_back(make_pair(3, 4));
	items.push_back(make_pair(1, 4));

	cout << knapsack01(items.begin(), 3, 5, back_inserter(res)) << endl;
	
	cout << "Items in the sack" << endl;
	for(auto it = res.begin(); it != res.end(); it++)
		cout << "wt: " << it->first << "\tvalue: " << it->second << endl;

}


