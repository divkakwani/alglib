// Test for sorting procedures in sort.h

#define CATCH_CONFIG_MAIN
#include <test/catch.hpp>

// File to test
#include <alglib/sort/sort.h>

#include <vector>

using namespace alglib::sort;

/* All the sorting procedures are differentially tested against
 * the std::sort function. The following cases are tested for 
 * each sorting function:
 * 	1. Empty containers
 *  2. Randomly filled containers
 *  3. Several different types - float, strings
 *  4. Invalid inputs - non-containers, non-iterable
 *  5. For each valid iterator category.  
 */

template<typename Container>
Container random_int_list (int sz)
{
	Container C;
	auto it = std::back_inserter (C);

	/* fill up the container */
	srand (time (0));
	std::generate_n (it, sz, rand);

	return C;
}


/* A test is performed as follows:
 * 	1. Create two identical containers filled randomly.
 *  2. Sort one of them - call it std_sorted - using std::sort.
 *  3. Sort the other, test_sorted, using the procedure under test.
 *  4. Assert their equality.
 */

TEST_CASE ("Merge sort", "[merge_sort]")
{
	std::vector<int> test_sorted, std_sorted;

	std::vector<int> sizes = {0, 1000, 1000000};

	for (int size : sizes)
    {
		test_sorted = std_sorted = std::move(random_int_list<decltype(std_sorted)> (size));

		merge_sort (test_sorted.begin(), test_sorted.end());
		std::sort (std_sorted.begin(), std_sorted.end());

		REQUIRE (test_sorted == std_sorted);
	}

    // const_iterators are invalid.
    // REQUIRE_THROWS (merge_sort (test_sorted.cbegin (), test_sorted.cend ()));
    
    // Check if it works for non-random access iterators.
}





