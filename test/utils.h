

#ifndef _UTILS_H
#define _UTILS_H

#include <sstream>
#include <string>
#include <iostream>
#include <vector>

template<typename _ForwardIterator>
std::string sprint(_ForwardIterator first, _ForwardIterator last) {
	std::ostringstream res;
	res << "[";
	for(;first != last; first++)	
		res << *first << ", ";
	res << "]";
	return res.str();
}

#endif
