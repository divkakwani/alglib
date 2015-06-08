/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

#include <alglib/graph/dfs.h>

namespace alglib {
namespace graph {


template<typename GraphType, typename OutputIter>
OutputIter topological_order(const GraphType& G, OutputIter dest) {
    return postorder_dfs(G, dest);
}

}  // end of graph namespace
}  // end of alglib namespace
