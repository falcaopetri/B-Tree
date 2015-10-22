#ifndef B_TREE_TOOLS_H
#define B_TREE_TOOLS_H

#if DEBUG
#include <stdio.h>
#endif

#include "btree.h"

void print_find(BTree *tree, int key) {
	printf("Key %d found at position %d\n", key, btree_find(tree, key).indice);
}

void print_find_n(BTree *tree, int *nums, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		print_find(tree, nums[i]);
	}
	printf("\n");
}

void print_find_assert_n(BTree *tree, int *nums, int *pos, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		int p = btree_find(tree, nums[i]).indice;
		printf("%d at %d\n", nums[i], p);
		assert(p == pos[i]);
	}
}

void print_insert(BTree *tree, int key) {
	btree_insert(tree, key, NULL);
	#if DEBUG
	printf("\n");
	#endif
}

void print_insert_n(BTree *tree, int *nums, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		print_insert(tree, nums[i]);
	}
	printf("\n");
}

void print_remove(BTree *tree, int key) {
	printf("Removing key: %d\n", key);
	print_find(tree, key);
	node_position pos = btree_remove(tree, key);
	if (pos.indice == -1)
		printf("Removing failed\n");
	else
		printf("Removed key: %d\n", key);
	print_find(tree, key);
	printf("\n");
}

void print_remove_n(BTree *tree, int *nums, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		print_remove(tree, nums[i]);
		printf("\n");
	}
}

#endif
