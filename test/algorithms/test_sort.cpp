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

class SortTest : public Test {
	void (*func)(vector<int>::iterator first, vector<int>::iterator last);
	const int test_count;
	public:
		SortTest(void (*sort_routine)(vector<int>::iterator first, vector<int>::iterator last), int tst_count);
		void run_tests();

};

SortTest::SortTest(void (*sort_routine)(vector<int>::iterator first, vector<int>::iterator last),
 													int tst_count) : test_count(tst_count) {
	func = sort_routine;
}

void SortTest::run_tests() {

	DataGenerator<vector<int>> dg;
	for(int _ = 0; _ < test_count; _++) {
		vector<int> subject = dg(10);
		vector<int> subject_sorted_std = subject;
		vector<int> subject_sorted_test = subject;
		sort(subject_sorted_std.begin(), subject_sorted_std.end());	// Sorting through STL function
		(*func)(subject_sorted_test.begin(), subject_sorted_test.end());	// Sorting through function to be tested;

		equal_to<vector<int>> predicate;
		assertPredicate(subject_sorted_std, subject_sorted_test, predicate);
	}
}

int main() {

	// Selection sort test
	SortTest st1(selection_sort, 100);
	st1.run_tests();
	st1.report();

	cout << endl;

	// Quick sort test
	SortTest st2(quick_sort, 100);
	st2.run_tests();
	st2.report();

	cout << endl;

	// Standard sort test
	SortTest st3(sort, 100);
	st3.run_tests();
	st2.report();

	cout << endl;

	// Merge sort test
	SortTest st4(merge_sort, 100);
	st4.run_tests();
	st4.report();

	cout << endl;

	return 0;
}
