#include "../test.h"
#include "../../src/algorithms/sort.h"
#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include "../data_generator.h"
#include "../utils.h"
#include <functional>

using namespace std;


template<typename Seq>
class SortTest : public Test {
	void (*func)(vector<int>::iterator first, vector<int>::iterator last);
	DataGenerator<Seq> gen;
	public:
		typedef typename Seq::iterator it_type;
		SortTest(void (*sort_routine)(it_type first, it_type last));
		void run_tests();
		void random_tests(int tst_cnt, int inp_sz);

};

template<typename Seq>
SortTest<Seq>::SortTest(void (*sort_routine)(it_type first, it_type last)) {
	func = sort_routine;
}

template<typename Seq>
void SortTest<Seq>::run_tests() {

	random_tests(100, 100);

}

template<typename Seq>
void SortTest<Seq>::random_tests(int tst_cnt, int inp_sz) {

	for(int _ = 0; _ < tst_cnt; _++) {
	Seq subject = gen.random_data(inp_sz);
	Seq subject_sorted_std = subject;
	Seq subject_sorted_test = subject;
	sort(subject_sorted_std.begin(), subject_sorted_std.end());	// Sorting through STL function
	(*func)(subject_sorted_test.begin(), subject_sorted_test.end());	// Sorting through function to be tested;

	assertPredicate(subject_sorted_std, subject_sorted_test, equal_to<vector<int>>());
	}
}

int main() {


	// Selection sort test
	SortTest<vector<int>> st1(selection_sort);
	st1.run_tests();
	st1.report();

	cout << endl;

	// Quick sort test
	SortTest<vector<int>> st2(quick_sort);
	st2.run_tests();
	st2.report();

	cout << endl;

	// Standard sort test
	SortTest<vector<int>> st3(sort);
	st3.run_tests();
	st2.report();

	cout << endl;

	// Merge sort test
	SortTest<vector<int>> st4(merge_sort);
	st4.run_tests();
	st4.report();

	cout << endl;

	return st1.get_status() | st2.get_status() | st3.get_status() | st4.get_status();
}
