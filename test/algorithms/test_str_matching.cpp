

#include <iostream>
#include <string>
#include "../data_generator.h"
#include "../utils.h"
#include "../test.h"
#include "../../src/algorithms/str_matching.h"

using namespace std;

class StrMatchingTest : public Test {
    DataGenerator<string> gen;
    int (*func)(string haystack, string needle);
  public:
    StrMatchingTest(int (*fn)(string haystack, string needle));
    void run_tests();
    void run_random_tests();
    void run_custom_tests();
};

StrMatchingTest::StrMatchingTest(int (*fn)(string haystack, string needle)) {
  func = fn;
}

void StrMatchingTest::run_tests() {
  run_random_tests();
  run_custom_tests();
}

void StrMatchingTest::run_random_tests() {
  const int pattern_sz = 10, search_sz = 1000;
  string pattern = gen.random_data(pattern_sz);
  string search = gen.random_data(search_sz);

  assert_(func(search, pattern) == search.find(pattern));
}

void StrMatchingTest::run_custom_tests() {

}

int main() {

  return 0;
}
