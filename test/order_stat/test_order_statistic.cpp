#include "../test.h"
#include "../../src/algorithms/order_statistic.h"
#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include "../data_generator.h"
#include "../utils.h"
#include <functional>
#include <iterator>
#include "../utils.h"

using namespace std;

#define PRINT(x) cout << #x << " : " << x << endl;

template<typename Seq>
class OrderStatisticTest : public Test {
		typedef typename Seq::iterator it_type;
		it_type (*func)(it_type, it_type, int);
	
	public:
		OrderStatisticTest(it_type (*fn)(it_type, it_type, int)) {
			func = fn;
		}
		
		void run_tests();
		
		void random_tests(int tst_cnt, int inp_sz);
};


template<typename Seq>
void OrderStatisticTest<Seq>::run_tests() {

	random_tests(100, 100);

}

template<typename Seq>
void OrderStatisticTest<Seq>::random_tests(int tst_cnt, int inp_sz) {

	DataGenerator<Seq> gen;
	
	for(int j = 0; j < tst_cnt; j++) {
		vector<int> v = gen.random_data(inp_sz);
		
		vector<int> sorted_v = v;
		sort(sorted_v.begin(), sorted_v.end());
		
		int i = rand() % inp_sz + 1;
		
		int res = *(sorted_v.begin() + i - 1);
		int test = *func(v.begin(), v.end(), i);		

		assert_(test == res);
			
	}
}



int main() {

	OrderStatisticTest<vector<int>> t(select_i);
	t.run_tests();
	t.report();

	return 0;
}
