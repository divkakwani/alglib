#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


int memo[100][100];

template<typename RandomAccessIter>
int knapsack01(RandomAccessIter in, int n, int cap) {

	if(n <= 0 || cap <= 0)
		return 0;
			
	if(memo[n][cap] == -1) {
		if(in->first > cap)
			memo[n][cap] = knapsack01(in + 1, n - 1, cap);
		else
			memo[n][cap] = max(knapsack01(in + 1, n - 1, cap), in->second + knapsack01(in + 1, n - 1, cap - in->first));

	}
	
	return memo[n][cap];

}


// Driver

int main() {

	memset(memo, 0xFF, 10000 * sizeof(int));
	
	vector<pair<int, int>> items, res;

	items.push_back(make_pair(7, 6));
	items.push_back(make_pair(7, 4));
	items.push_back(make_pair(8, 4));

	cout << knapsack01(items.begin(), 3, 5) << endl;

}

		
	
