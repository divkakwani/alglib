/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */
 
#pragma once


template<typename AssocT, typename Aggr>
class SegmentTree {

 private:

    vector<AssocT> sat_data;

    int left(int node)  { return node << 1; }
    int right(int node) { return (node << 1) + 1; }

    


 public:

    SegmentTree(std::vector<AssocT>& v);
 
    // point update
    void update(int i, AssocT& new_val);

    // range update
    template<typename UnaryFunc>
    void update(int i, int j, UnaryFunc change);



    AssocT range_query(int i, int j);

    
};

