/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


#include <map>
#include <stdexcept>

namespace alglib {
namespace graph {

template<typename GraphType, typename PropertyType>
class vertex_property {

    typedef typename GraphType::vertex_type vertex_type;
 private:
    std::map<vertex_type, PropertyType> property;

 public:
    /** 
     * \brief vertex_property constructor 
     * \param G The graph on which the property is to be defined
     * \param default_val (optional) Default property of each vertex
     */
    explicit vertex_property(const GraphType& G, 
                             const PropertyType& default_val = PropertyType()) {
        for(auto it = G.vbegin(); it != G.vend(); it++)
            property[*it] = default_val;
    }
    
    
    vertex_property(const vertex_property& P) = default;

    /*
     * \brief move-constructor
     */
    vertex_property(vertex_property&& P) : property(std::move(P.property)) {}

    /*
     * \breif get the reference to the property associated with a vertex
     * \param v vertex whose property is sought
     * \return A reference to the property of the vertex
     */
    PropertyType& operator[] (const vertex_type& v) {
        typename std::map<vertex_type, PropertyType>::iterator it;
        if((it = property.find(v)) == property.end())
            throw std::domain_error("The vertex doesn't exist in the supplied graph");
        return it->second;
    }

    PropertyType operator() (const vertex_type& v) const { 
        typename std::map<vertex_type, PropertyType>::const_iterator it;  // const-ness imperative
        if((it = property.find(v)) == property.end())
            throw std::domain_error("The vertex doesn't exist in the supplied graph");
        return it->second;
    }
};



}  // end of graph namespace
}  // end of alglib namespace
