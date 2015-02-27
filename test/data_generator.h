

#ifndef _DATAGENERATOR_H
#define _DATAGENERATOR_H

/*
	This module handles the input data generation for testing algorithms
	present in this library.
*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <ctime>

/*
	The class is templatized by the container which is to be filled
*/
template<typename Container>
class DataGenerator {
	public:
		typedef typename Container::value_type val_type;
		DataGenerator() {
			srand(time(0));	//	Seed the psuedo-random number generator with 1. Set seed = time(0) to obtain distinct
							//	sequence of random numbers in each run
		}
		val_type random_datum() {
			val_type elt;
			char* mem = reinterpret_cast<char*>(&elt);
			for(int i = 0; i < sizeof(val_type); i++)
				*mem = rand() % 128;
			return elt;
		}

		Container random_data(int sz) {
			Container res;
			for(int i = 0; i < sz; i++) {
				res.insert(res.end(), random_datum());
			}
			return res;
		}

};



#endif
