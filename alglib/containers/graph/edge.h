/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <type_traits>

template<typename vertex_t, typename attr_t = int, typename Enable = void>
struct edge_t : public attr_t {

    vertex_t from;
    vertex_t to;
};


template<typename vertex_t, typename attr_t>
struct edge_t<vertex_t, attr_t,
              typename std::enable_if<std::is_fundamental<attr_t>::value>::type> {
              
    vertex_t from;
    vertex_t to;
    attr_t attribute;
};

/*

template<typename vertex_t, typename attr_t>
edge_t<vertex_t, attr_t> make_edge (vertex_t from, vertex_t to,
                                    attr_t attribute = -1) {
    return edge_t<vertex_t, attr_t> {from, to, attribute};
}
*/



