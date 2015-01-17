

#ifndef _DATAGENERATOR_H
#define _DATAGENERATOR_H


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <ctime>

/*
	The class is templatized by the container which is to be filled.
		
	
*/
template<typename T, template<class, class Alloc = std::allocator<T>> class Seq>
class DataGenerator {
	public:
		DataGenerator() {
			srand(time(0));	//	Seed the psuedo-random number generator with 1. Set seed = time(0) to obtain distinct 
							//	sequence of random numbers in each run
		}
		T random_datum() {
			T elt;
			char* mem = reinterpret_cast<char*>(&elt);
			for(int i = 0; i < sizeof(T); i++)
				*mem = rand() % 256;
			return elt;
		}
		
		Seq<T> operator()(int sz) {
			Seq<T> res;
			for(int i = 0; i < sz; i++) {
				res.insert(res.end(), random_datum());
			}
			return res;
		} 
		
};



#endif
