#ifndef _STR_MATCHING_
#define _STR_MATCHING_

#include <string>
#include <cmath>


#include <iostream>
using namespace std;


/*

  * String matching algorithms covered :
  *  Naive
  *  Rabin-Karp
  *  Finite automaton
  *  Knuth-Morris-Pratt
  *  Horspool's algorithm

*/

size_t naive_str_matching(const std::string& text, const std::string& pattern) {
	/**
	The naive algorithm checks for the equivalence of pattern P
	with the substring of the text T[s:s+m-1] starting with the
	shift s = 0 and going all the way to s = n-m.
	**/

	int s = 0;
	int n = text.length(), m = pattern.length();
	for(s = 0; s <= n - m; s++)
		// Loop Invariant : The pattern doesn't exist in T[0:s-1] but may exist
		// in T[s, n].
		if(text.substr(s, m) == pattern)
			return s;
	return std::string::npos;

	/**
	Performance
		The best case occurs when the substring with shift = 0 matches the
		pattern giving a time complexity of O(m).
		The worst case occurs when the pattern matches all but the last character
		of the m-substring produced by each of the shift. In this case, the time
		complexity is O((n-m)m).
		In the average case, the expected succesful consecutive character matches
		while comparing a random pattern with a random m-substring is given by:
		Summation of [(1/len(Σ))^k * (len(Σ)-1)/len(Σ)] * (k+1) from k = 0 to m
		where the quantity in [] is the probability of having k successful matches
		followed by one unsuccesful match.
		For english alphabet, the summation is close to 1. Hence, in average case
		the time complexity is O(n-m).


	Proof of Correctness
		Supposing that T[s, s+m-1] = P, the match will be detected in the sth
		iteration of the loop. If however a match doesn't exist, the test will
		fail in each of the iteration and a no-match-found identifier will be
		returned.
	**/
}

// Helper procedure for rabin-karp algorithm
static long int poly_hash(const std::string& input, int m) {
	const int radix = 10;
	const long int Q = 997;
	long int hash_val = 0;
	for(int i = 0; i < m; i++)
		hash_val = (hash_val * radix + input[i]) % Q;
	return hash_val;
}

size_t rabin_karp(const std::string& text, const std::string& pattern) {
	/**
	The Rabin-Karp algorithm computes a hash of the m-substring with shift s
	and then compares it with the pattern. It gains on the naive algorithm by using
	a rolling hash function which allows one to compute hash value of T[s+1:s+m]
	from T[s:s+m-1] in constant time.
	**/

	int m = pattern.length();
	int n = text.length();
	const long int R = 10;
	long int pattern_hash = poly_hash(pattern, m);
	long int text_hash = poly_hash(text, m);
	long int R_m_minus_1 = std::pow(R, m - 1);

	if(pattern_hash == text_hash)
		if(pattern == text.substr(0, m))
			return 0;
	for(int s = 1; s <= n - m; s++) {
		text_hash = (text_hash - R_m_minus_1 * text[s-1]) * R + text[s + m - 1];
		if(pattern_hash == text_hash)
			if(pattern == text.substr(s, m))
				return s;
	}

	return std::string::npos;
}

/*
size_t horspool(std::string text, std::string pattern) {

}
*/

#endif
