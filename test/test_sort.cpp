
#include "test.h"
#include "../src/sort.h"
#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include "DataGenerator.h"
#include "utils.h"
#include <functional>

using namespace std;

class SortTest : public Test {
	void (*func)(vector<int>::iterator first, vector<int>::iterator last);
	const int test_count;
	public:
		SortTest(void (*sort_routine)(vector<int>::iterator first, vector<int>::iterator last), int tst_count);
		void run_tests();
		float get_runtime();

};

SortTest::SortTest(void (*sort_routine)(vector<int>::iterator first, vector<int>::iterator last), int tst_count) : test_count(tst_count) {
	func = sort_routine;
}

void SortTest::run_tests() {

	DataGenerator<int, vector> dg;
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

float SortTest::get_runtime() {
	DataGenerator<int, vector> dg;
	vector<vector<int>> tests;

	// Fill the test vectors with pseudorandom integers
	for(int n = 0; n < test_count; n++)
		tests.insert(tests.end(), dg(1000));


	clock_t start_time = clock();	// start the timer

	for(auto& test : tests)
		func(test.begin(), test.end());

	clock_t end_time = clock();		// stop the timer

	return float(end_time - start_time) / CLOCKS_PER_SEC;

}

int main() {

	// Selection sort test
	SortTest st1(selection_sort, 100);
	st1.run_tests();
	cout << "Time taken for selection sort : " << st1.get_runtime() << endl;
	st1.report();

	cout << endl;

	// Quick sort test
	SortTest st2(quick_sort, 100);
	st2.run_tests();
	cout << "Time taken for quick sort : " << st2.get_runtime() << endl;
	st2.report();

	cout << endl;

	// Standard sort test
	SortTest st3(sort, 100);
	st3.run_tests();
	cout << "Time taken for std sort : " <<  st3.get_runtime() << endl;
	st2.report();

	cout << endl;

	// Merge sort test
	SortTest st4(merge_sort, 100);
	st4.run_tests();
	cout << "Time taken for merge sort : " << st4.get_runtime() << endl;
	st4.report();

	cout << endl;

	return 0;
}
