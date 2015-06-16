/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <vector>
#include <memory>

#include <alglib/bimap/bimap.h>
#include <alglib/graph/models/graph_model.h>

namespace alglib {
namespace graph {
namespace models {

template<typename vertex_t, typename edge_t>
class adj_matrix : public graph_model<vertex_t, edge_t> {
   
 public:
    /* typedefs */ 
    typedef vertex_t vertex_type;
    typedef edge_t edge_type;
    typedef typename alglib::bimap::bimap<vertex_t, int>::type1_iterator const_viterator;
 
 private:

    /* Establishes a one-to-one mapping between vertices and ints */
    alglib::bimap::bimap<vertex_t, int> vertex_to_int;
   
    /* The adjacent matrix is represented as a vector of vectors.
     * Each cell, matrix[i][j], stores a unique_ptr to the corresponding edge if
     * there exists an edge between vertex i and vertex j, otherwise it refers to
     * null. The edge is the cell's copy of the edge and hence it is its owner.
     * Once it is set to null, the edge is automatically freed.
     */
    std::vector<std::vector<std::unique_ptr<edge_t>>> matrix;

    /* vsize tells the no of vertices; The is required because the `matrix` can be
     * preallocated vertices. Hence, its size would be larger than actual vsize.
     */
    int vsize;

    /* The following members record the in-degrees and out-degrees - to fasten
     * the indeg and outdeg methods. These require to be updated by every mutating method
     * on the graph.
     */
    std::vector<int> indeg_rec;
    std::vector<int> outdeg_rec;

    // no of edges
    int esize;
    
    /** \brief Grows the matrix to be atleast as large as dim x dim.
     *
     *  It is not bound to just increase the matrix size from nxn to (n+1)x(n+1).
     *  For efficiency reason, it can increase the size to larger dimensions to 
     *  amortize the cost of add_vertex.
     */
    void grow_matrix(int dim);

 public:

    adj_matrix() = default;

    void add_vertex(const vertex_t& u) {
        vertex_to_int.insert(u, vsize++);
        grow_matrix(vsize);
    }

    /* It starts by finding the vertex to be removed and then swap that
     * vertex with the last vertex.
     */
    void remove_vertex(const vertex_t& u) {
        
        int im = vertex_to_int.get_image(u);

        /* Changes in bimap
         * Assign `im` to the last vertex and release the int held by it earlier.
         * Changes to adjaceny matrix
         * Replace the `im`th row and `im`th col with the last row and last col respectively, 
         * releasing the edges held earlier by the `im`th row and col.
         */
        // Bimap changes
        vertex_to_int.remove_domain_elt(u);
        vertex_t v = vertex_to_int.get_preimage(vsize-1);  // last vertex is vsize-1
        vertex_to_int.remove_codomain_elt(vsize-1);
        vertex_to_int.insert(v, im);  // now insert (last vertex, image(u))

        // adjacency matrix changes
        
        // copy the col
        for(int i = 0; i < vsize; i++)
            matrix[i][im] = matrix[i][vsize-1];

        // copy the row
        for(int i = 0; i < vsize-1; i++)
            matrix[im][i] = matrix[vsize-1][i];

        --vsize;
    }

    void add_edge(const vertex_t& u, const vertex_t& v, const edge_t& e) {
        int i = vertex_to_int.get_image(u);
        int j = vertex_to_int.get_image(v);
        matrix[i][j] = e;
        ++esize;
    }

    void add_edge(const edge_t& e) {
        add_edge(e.from, e.to, e);
    }

    void remove_edge(const edge_t& e) {
        int i = vertex_to_int(e.from);
        int j = vertex_to_int(e.to);
        matrix[i][j].reset();
        ++esize;
    }

    int indeg(const vertex_t& u) const {
        return indeg_rec[vertex_to_int.get_image(u)];
    }
    int outdeg(const vertex_t& u) const {
        return indeg_rec[vertex_to_int.get_image(u)];
    }
    int num_vertices() const {
        return vsize;
    }
    int num_edges() const {
        return esize;
    }

    const_viterator vbegin() const {
        vertex_to_int.domain_begin();
    }
    const_viterator vend() const {
        return vertex_to_int.domain_end();
    }

};

}  // end of models namespace
}  // end of graph namespace
}  // end of alglib namespace

