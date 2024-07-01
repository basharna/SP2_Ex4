/*
ID: 212487144
Email: nbashar4@gmail.com
*/

#include <iostream>
#include <string>
#include <fstream>
#include "tree.hpp"
#include "complex.hpp"

int main()
{
    Tree<double> tree;
    tree.add_root(1.1);
    tree.add_sub_node(1.1, 1.2);
    tree.add_sub_node(1.1, 1.3);
    tree.add_sub_node(1.2, 1.4);
    tree.add_sub_node(1.2, 1.5);
    tree.add_sub_node(1.3, 1.6);


    // The tree should look like:
    /**
     *         root = 1.1
     *        /         \
     *      1.2        1.3
     *     /   \       /
     *    1.4  1.5   1.6
     */

    cout << "Pre-order: ";
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "Post-order: ";
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
        cout << *it << " ";
    cout << endl;
    // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "In-order: ";
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it)
        cout << *it << " ";
    cout << endl;
    // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "BFS-scan: ";
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it)
        cout << *it << " ";
    cout << endl;
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "DFS-scan: ";
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it)
        cout << *it << " ";
    cout << endl;
    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "Range-based for loop: ";
    for (auto node : tree)
    {
        cout << node << " ";
    }
    cout << endl;
    // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    Tree<double, 3> three_ary_tree;
    three_ary_tree.add_root(1.1);
    three_ary_tree.add_sub_node(1.1, 1.2);
    three_ary_tree.add_sub_node(1.1, 1.3);
    three_ary_tree.add_sub_node(1.1, 1.4);
    three_ary_tree.add_sub_node(1.2, 1.5);
    three_ary_tree.add_sub_node(1.3, 1.6);

    three_ary_tree.print_tree();

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    Tree<Complex, 4> complex_tree;
    complex_tree.add_root(Complex(1, 1));
    complex_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    complex_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    complex_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    complex_tree.add_sub_node(Complex(2, 2), Complex(5, 5));
    complex_tree.add_sub_node(Complex(3, 3), Complex(6, 6));
    complex_tree.add_sub_node(Complex(3, 3), Complex(7, 7));
    complex_tree.add_sub_node(Complex(4, 4), Complex(8, 8));
    complex_tree.add_sub_node(Complex(6, 6), Complex(9, 9));
    complex_tree.add_sub_node(Complex(1, 1), Complex(10, 10));
    complex_tree.add_sub_node(Complex(1, 1), Complex(11, 11));
    

    cout << complex_tree;

    return 0;
}