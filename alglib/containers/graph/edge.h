/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

typedef int NIL;
const NIL nil_val = -1;

template<typename vertex_t, typename attr_t = NIL>
struct edge_t {
    vertex_t from;
    vertex_t to;
    attr_t attribute;

    typedef vertex_t vertex_type;
    typedef attr_t   attribute_type;
};


template<typename vertex_t, typename attr_t = NIL>
edge_t make_edge (vertex_t from, vertex_t to, attr_t attribute = nil_val) {
    return edge_t {from, to attribute};
}
