
#ifndef _EDGE_H
#define _EDGE_H

template<typename vertex_t>
class edge {

	public:
		virtual vertex_t& from() const = 0;
		virtual vertex_t& to() const = 0;

};

template<typename vertex_t, typename weight_t>
class weighted_edge : public edge<vertex_t> {

	public:
		virtual weight_t weight() const;

};

#endif
