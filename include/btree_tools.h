#ifndef B_TREE_TOOLS_H
#define B_TREE_TOOLS_H

#include <stdio.h>

#include "btree.h"

void btree_dfs_node(node_t *node, int level);
void btree_dfs(BTree *tree);

void print_find(BTree *tree, int key);
void print_find_n(BTree *tree, int *nums, int n);
void print_find_assert_n(BTree *tree, int *nums, int *pos, int n);

void print_insert(BTree *tree, int key);
void print_insert_n(BTree *tree, int *nums, int n);

void print_remove(BTree *tree, int key);
void print_remove_n(BTree *tree, int *nums, int n);

#endif
