/*
ID: 212487144
Email: nbashar4@gmail.com
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"

TEST_CASE("Tree functionality")
{
    Tree<int, 2> tree;

    SUBCASE("Add root and check")
    {
        tree.add_root(10);
        auto it = tree.begin();
        REQUIRE(*it == 10);
    }

    SUBCASE("Add sub-nodes and check")
    {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);

        vector<int> values;
        for (auto it : tree)
        {
            values.push_back(it);
        }
        REQUIRE(values == vector<int>{10, 20, 30, 40});
    }

    SUBCASE("Check clear method")
    {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);

        tree.clear();

        REQUIRE(tree.begin() == tree.end());
    }

    SUBCASE("Check empty tree behavior")
    {
        REQUIRE(tree.begin() == tree.end());
    }

    SUBCASE("Add nodes and check iterator behavior")
    {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);

        auto it = tree.begin();
        REQUIRE(*it++ == 10);
        REQUIRE(*it++ == 20);
        REQUIRE(*it++ == 30);
        REQUIRE(*it++ == 40);
        REQUIRE(it == tree.end());
    }

    SUBCASE("Iterate over empty tree")
    {
        for (auto it : tree)
        {
            // Should not enter this loop since tree is empty
            cout << it << endl;
            CHECK(false);
        }
    }

    SUBCASE("Iterate using different traversal methods")
    {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);

        // Pre-order traversal
        vector<int> pre_order;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it)
        {
            pre_order.push_back(*it);
        }
        REQUIRE(pre_order == vector<int>{10, 20, 40, 30});

        // Post-order traversal
        vector<int> post_order;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it)
        {
            post_order.push_back(*it);
        }
        REQUIRE(post_order == vector<int>{40, 20, 30, 10});
    }

    SUBCASE("Check BFS scan")
    {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);

        vector<int> bfs_scan;
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it)
        {
            bfs_scan.push_back(*it);
        }
        REQUIRE(bfs_scan == vector<int>{10, 20, 30, 40});
    }

    SUBCASE("Check DFS scan")
    {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);

        vector<int> dfs_scan;
        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it)
        {
            dfs_scan.push_back(*it);
        }
        REQUIRE(dfs_scan == vector<int>{10, 20, 40, 30});
    }

    SUBCASE("Transform to min-heap")
    {
        tree.add_root(40);
        tree.add_sub_node(40, 30);
        tree.add_sub_node(40, 50);
        tree.add_sub_node(30, 20);
        tree.add_sub_node(50, 10);

        auto it = tree.myHeap();
        vector<int> heap_values;
        for (; it != tree.end(); ++it)
        {
            heap_values.push_back(*it);
        }
        REQUIRE(heap_values == vector<int>{10, 20, 30, 40, 50});
    }

    SUBCASE("Check size of tree")
    {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);

        REQUIRE(tree.size() == 4);
    }

    // Add more test cases as needed...
}
