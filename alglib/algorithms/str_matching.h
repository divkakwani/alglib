// Document this file
/** @file */ 

# pragma once

#include <string>
#include <cmath>
#include <climits>

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




size_t horspool(const std::string& text, const std::string& pattern) {

	int skip_table[UCHAR_MAX + 1];
	int n = text.length(), m = pattern.length();

	// Initialize each of the index of the shift table to m.
	std::fill_n(skip_table, UCHAR_MAX + 1, m);
	
	// Compute the skip table for the given pattern.
	for(int i = 0; i < m - 1; i++) {
		skip_table[pattern[i]] = m - i - 1;
	}

	// Do the string comparison

	// align the pattern shifted with s in [0, n-m] with the text
	for(int shift = 0; shift <= n - m;) {

		// For every shift, start comparing from back
		int i = m - 1;

		// Keep moving to the right until a mismatch is detected.
		while(i >= 0 && (text[shift + i] == pattern[i]))
			i--;
		
		if(i == -1)
			// if the pattern matched completely with the text
			return shift;
			
		shift += skip_table[text[shift + m - 1]];
	}

	return std::string::npos;

}

/**
 * \brief Performs substring search in a given string
 * \param text The text in which the pattern is to be searched
 * \param pattern The string to be searched
 * \return The starting position of the first occurence of pattern in text
 */
size_t kmp(const std::string& text, const std::string& pattern) {


}

