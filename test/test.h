
#include <iostream>
#include <string>
#include "utils.h"

#define assert_(expr) \
	eval_test(expr, #expr, __FILE__, __LINE__)

#define assertPredicate(lhs, rhs, predicate) \
	eval_test(predicate(lhs, rhs), #predicate "(" #lhs ", = " #rhs, __FILE__, __LINE__, sprint(lhs.begin(), lhs.end()))


/* A general test class that describes the minimal interface of a test class.
	This class has pass/fail counters, a method to add test results and a purely virtual method to run tests.
	The classes deriving from Test must override run_tests() at the least. The details of specifying the tests
	is left to the derived classes.
*/
class Test {
	private:
		int passCount;
		int failCount;
	public:
		bool verbose;
		Test();
		void eval_test(bool expr, const std::string& exprStr, const std::string& fname, long lineno, std::string error_input = std::string());
		virtual void run_tests() = 0;
		void report();
		
};

Test::Test() {
	passCount = failCount = 0;
	verbose = false;
}

void Test::eval_test(bool expr, const std::string& exprStr, const std::string& fname, long lineno, std::string error_input) {
	// Increments pass/fail counter by checking whether expr evaluates to true/false
	if(expr) {
		passCount++;
		if(verbose)	std::cout << fname << ": " << exprStr << " (Line: " << lineno << ") : Passed\n";
	}
	else {
		failCount++;
		std::cout << "Test failed on input : " << error_input << std::endl; 
		if(verbose)	std::cout << fname << ": " << exprStr << " (Line: " << lineno << ") : Failed\n";
	}
}

void Test::report() {
	std::cout << "\nTest Report\n";
	std::cout << "=====================================\n";
	std::cout << "Cases Passed: " << passCount << std::endl;
	std::cout << "Cases Failed: " << failCount << std::endl;
}



