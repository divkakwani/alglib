/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#include <iostream>
#include "../../../src/containers/heap/binary_heap.h"

using std::cout;
using std::endl;

int main() {
    /* unkeyed binary heap test */
    unkeyed_binary_heap<int> h;
    h.insert(4);
    h.insert(2);
    h.insert(12);
    while (!h.empty()) {
        cout << h.get_min() << "\t";
        h.delete_min();
    }
    cout << endl;

    /* keyed binary_heap_test */
    binary_heap<int, int> kh;
    kh.insert(4, 20);
    kh.insert(5, 10);
    kh.insert(10, 30);

    while (!kh.empty()) {
        cout << kh.get_min_elt() << "\t";
        kh.delete_min();
    }
    cout << endl;
}
