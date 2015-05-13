/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#pragma once

template<typename node_type>
class BST {

	node_type& root;

};

template<typename node_type>
class BST_node {

    node_type data;
	vector<node_type&> children;

}
