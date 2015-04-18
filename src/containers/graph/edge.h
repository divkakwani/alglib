
#ifndef _EDGE_H
#define _EDGE_H

#include "vertex.h"

class edge {
	public:
		virtual int hash_code() = 0;
		virtual vertex& either() = 0;
		virtual vertex& other() = 0;
};

class weighted_edge : public edge {
	public:
		virtual int weight();
};

class directed_edge {
	public:
		virtual int hash_code() = 0;
		virtual vertex& from() = 0;
		virtual vertex& to() = 0;
};

class weighted_directed_edge : public directed_edge {
	public:
		virtual int weight();
};


#endif
