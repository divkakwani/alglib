/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


#pragma once

/**
 * \brief The interface of a graph model.
 * 
 * A graph model must implement this interface to be usable
 * with graph types in this library.
 */

template<typename vertex_t, typename edge_t>
class graph_model {

 public:
    /// Returs true if the two given vertices are adjacent, otherwise false
    bool are_adj(const vertex_t&, const vertex_t&) const;
    
    
    void add_vertex(const vertex_t& v);;
    void add_edge(const vertex_t& u, const vertex_t& v, const edge_t& e);
    void remove_vertex(const vertex_t& v);
    void remove_edge(const edge_t& e);
        
    int indeg(vertex_t v) const;
    int outdeg(vertex_t v) const;

    int num_vertices() const;
    int num_edges() const;


    const_viterator vbegin();
    const_viterator vend();
    const_eiterator ebegin();
    const_eiterator eend();
    const_viterator avbegin(const vertex_t& v);
    const_viterator avend(const vertex_t& v);
    const_eiterator aebegin(const vertex_t& v);
    const_eiterator aeend(const vertex_t& v);

};


