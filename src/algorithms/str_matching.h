#ifndef _STR_MATCHING_
#define _STR_MATCHING_

#include <string>

/*

  * String matching algorithms covered :
  *  Naive
  *  Rabin-Karp
  *  Finite automaton
  *  Knuth-Morris-Pratt
  *  Horspool's algorithm

*/

int naive_str_matching(std::string text, std::string pattern) {
	/**
		The naive algorithm checks for the equivalence of pattern P
		with the substring of the text T[s:s+m-1] starting with the
		shift s = 0 and going all the way to s = n-m.
		
	**/
	
	int s = 0;
	int n = text.length(), m = pattern.length();
	for(s = 0; s <= n - m; s++) {
		if(text.substr(s, s + m) == pattern)
			return s;
	return string::npos;
}


#endif
