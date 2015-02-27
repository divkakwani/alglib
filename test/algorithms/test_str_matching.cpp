

#include <iostream>
#include <string>
#include "../data_generator.h"
#include "../utils.h"
#include "../test.h"
#include "../../src/algorithms/str_matching.h"

using namespace std;

class StrMatchingTest : public Test {
    DataGenerator<string> gen;
    size_t (*func)(const string& text, const string& pattern);
  public:
    StrMatchingTest(size_t (*fn)(const string& text, const string& search));
    void run_tests();
    void run_random_tests();
    void run_custom_tests();
};

StrMatchingTest::StrMatchingTest(size_t (*fn)(const string& text, const string& search)) {
  func = fn;
}

void StrMatchingTest::run_tests() {
  run_random_tests();
  run_custom_tests();
}

void StrMatchingTest::run_random_tests() {
  const int test_cases = 100;
  const int pattern_sz = 2, search_sz = 100;


  for(int i = 0; i < test_cases; i++) {
    string pattern = gen.random_data(pattern_sz);
    string search = gen.random_data(search_sz);
    assert_(func(search, pattern) == search.find(pattern));
  }
}

void StrMatchingTest::run_custom_tests() {

}

int main() {

	StrMatchingTest routine1(naive_str_matching);
	routine1.run_tests();
	routine1.report();


  StrMatchingTest routine2(rabin_karp);
  routine2.run_tests();
  routine2.report();

  StrMatchingTest routine3(horspool);
  routine3.run_tests();
  routine3.report();



	return 0;
}
