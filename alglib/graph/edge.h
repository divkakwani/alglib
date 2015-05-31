/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <iostream>

template<typename vertex_t, typename attr_t = void>
struct edge_t {
              
    vertex_t from;
    vertex_t to;
    attr_t attribute;

    edge_t(const vertex_t& u, const vertex_t& v, const attr_t& attr) {
        from = u;
        to = v;
        attribute = attr;
    }
    
    bool operator==(const edge_t<vertex_t, edge_t>& other) const
    { return attribute == other.attribute; }

    bool operator!=(const edge_t<vertex_t, edge_t>& other) const 
    { return attribute != other.attribute; }

    bool operator>(const edge_t<vertex_t, edge_t>& other) const 
    { return attribute > other.attribute; }

    bool operator<(const edge_t<vertex_t, edge_t>& other) const 
    { return attribute < other.attribute; }

    bool operator>=(const edge_t<vertex_t, edge_t>& other) const 
    { return attribute >= other.attribute; }

    bool operator<=(const edge_t<vertex_t, edge_t>& other) const 
    { return attribute <= other.attribute; }
};

template<typename vertex_t, typename attr_t>
std::ostream& operator<<(std::ostream& out, const edge_t<vertex_t, attr_t>& e) {

    out << "(from: " << e.from << ", to: " << e.to
        << ", attr: " << e.attribute << ")";
    return out;
}


template<typename vertex_t, typename attr_t>
edge_t<vertex_t, attr_t> make_edge(vertex_t from, vertex_t to,
                                   attr_t attribute) {
    return edge_t<vertex_t, attr_t>(from, to, attribute);
}

// Specialization for types when the attribute is void
template<typename vertex_t>
struct edge_t<vertex_t, void> : public edge_t<vertex_t, int> {

    edge_t(const vertex_t& u, const vertex_t v) : edge_t<vertex_t, int>(u, v, 1) {}

};

