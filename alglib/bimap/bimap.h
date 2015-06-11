/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <map>
#include <vector>
#include <stdexcept>
#include <boost/iterator/transform_iterator.hpp>

namespace alglib {
namespace bimap {

/*
 * \brief Data structure to hold bijective mappings
 *
 * Every element in the domain and the codomain must be distinct.
 */
template<typename type1, typename type2>
class bimap {

 private:


    /* All the elements in the domain are put into `domain` where each of the element
     * is given a distinct int. Same goes with the elements of codomain.
     */
    std::map<type1, int> domain;
    std::map<type2, int> codomain;

    /*  Upon every insertion, a new entry is made in `directory` which stores a pair of iterators,
     *  one referring to the element inserted in domain, the other to the element inserted in the
     *  codomain against the integer assigned to them. 
     */
    typedef std::pair<typename std::map<type1, int>::iterator,
                      typename std::map<type2, int>::iterator> 
            dir_entry;

    std::map<int, dir_entry> directory;  // An indirection

    /* total elements in domain/codomain */
    int dir_entries;

    template<typename T>
    struct select1st : public std::unary_function<T, typename T::first_type> {
        typename T::first_type operator()(const T& p) const { return p.first; };
    };

    select1st<std::pair<type1, int>> get_domain_elt;
    select1st<std::pair<type2, int>> get_codomain_elt;

 public:

    /* typedefs */
    typedef type1 domain_type;
    typedef type2 codomain_type;
    typedef boost::transform_iterator<select1st<std::pair<domain_type, int>>, 
                                      typename std::map<domain_type, int>::const_iterator>
            domain_iterator;
    typedef boost::transform_iterator<select1st<std::pair<codomain_type, int>>, 
                                      typename std::map<codomain_type, int>::const_iterator>
            codomain_iterator;


    /* ctors */
    bimap();
    bimap(const bimap&) = default;
    bimap(bimap&&);

    void insert(const type1& elt1, const type2& elt2);

    const codomain_type& get_image(const domain_type& elt) const;
    const domain_type& get_preimage(const codomain_type& elt) const;

    void remove_domain_elt(const domain_type& elt);
    void remove_codomain_elt(const codomain_type& elt);

    /* Iterator-returning methods */
    domain_iterator domain_begin() const;
    domain_iterator domain_end() const;
    codomain_iterator codomain_begin() const;
    codomain_iterator codomain_end() const;
};

template<typename type1, typename type2>
bimap<type1, type2>::bimap() {
    dir_entries = 0;
}

/* Move-constructor */
template<typename type1, typename type2>
bimap<type1, type2>::bimap(bimap&& b) : domain(std::move(b.domain)), 
                                        codomain(std::move(b.codomain)),
                                        directory(std::move(b.directory)),
                                        dir_entries(b.dir_entries) {}

template<typename type1, typename type2>
void bimap<type1, type2>::insert(const type1& elt1, const type2& elt2) {

    auto ret1 = domain.insert(std::make_pair(elt1, dir_entries));
    auto ret2 = codomain.insert(std::make_pair(elt2, dir_entries));

    // check if elt1 or elt2 already existed
    if(!ret1.second or !ret2.second)
        throw std::domain_error("Either or both of the element already exists");
    
    // record it in the directory
    directory[dir_entries] = std::make_pair(ret1.first, ret2.first);

    ++dir_entries;
}

template<typename type1, typename type2>
const type2& bimap<type1, type2>::get_image(const type1& elt) const {

    auto it = domain.find(elt);
    if(it == domain.end())
        throw std::out_of_range("The key doesn't exist");

    return (directory.at(it->second).second)->first;
}

template<typename type1, typename type2>
const type1& bimap<type1, type2>::get_preimage(const type2& elt) const {

    auto it = codomain.find(elt);
    if(it == codomain.end())
        throw std::out_of_range("The key doesn't exist");

    return (directory.at(it->second).first)->first;
}


template<typename type1, typename type2>
void bimap<type1, type2>::remove_domain_elt(const type1& elt) {
    
    auto domain_it = domain.find(elt);
    if(domain_it == domain.end())
        throw std::out_of_range("element doesn't exist");

    auto dir_entry = *directory[domain_it->second];
    auto it_pair = dir_entry->second;

    // Now erase the domain and codomain entry
    domain.erase(it_pair->first);
    codomain.erase(it_pair->second);

    // finally, delete the directory entry)
    directory.erase(dir_entry);
}


template<typename type1, typename type2>
void bimap<type1, type2>::remove_codomain_elt(const type2& elt) {
    
    auto codomain_it = codomain.find(elt);
    if(codomain_it == codomain.end())
        throw std::out_of_range("element doesn't exist");

    auto dir_entry = *directory[codomain_it->second];
    auto it_pair = dir_entry->second;

    // Now erase the domain and codomain entry
    domain.erase(it_pair->first);
    codomain.erase(it_pair->second);

    // finally, delete the directory entry)
    directory.erase(dir_entry);
}


/* Iterator-returning functions start here */

template<typename type1, typename type2>
typename bimap<type1, type2>::domain_iterator 
bimap<type1, type2>::domain_begin() const {
    return boost::make_transform_iterator(domain.begin(), get_domain_elt);
}

template<typename type1, typename type2>
typename bimap<type1, type2>::domain_iterator 
bimap<type1, type2>::domain_end() const {
    return boost::make_transform_iterator(domain.end(), get_domain_elt);
}

template<typename type1, typename type2>
typename bimap<type1, type2>::codomain_iterator 
bimap<type1, type2>::codomain_begin() const {
    return boost::make_transform_iterator(codomain.begin(), get_codomain_elt);
}

template<typename type1, typename type2>
typename bimap<type1, type2>::codomain_iterator 
bimap<type1, type2>::codomain_end() const {
    return boost::make_transform_iterator(codomain.end(), get_codomain_elt);
}


}  // end bimap namespace
}  // end alglib namespace

