/*
	B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
	DC - UFSCar - São Carlos - 2015
 */
#include "btree_tools.h"

void _btree_dfs_node(node_t *node, int level) {
	assert(node != NULL);

	int i;
	if (!node->is_leaf) {
		for (i = 0; i < node->n_keys+1; ++i) {
			_btree_dfs_node(node->children[i], level+1);
		}
	}

	printf("\tAlgum nó no nível %d possui %d chave(s): ", level, node->n_keys);
	for (i = 0; i < node->n_keys; ++i) {
		if (i != 0) printf(" ");
		printf("%d", node->keys[i]->key);
	}
	printf("\n");
}

void btree_dfs(BTree *bt) {
	assert(bt != NULL);
	_btree_dfs_node(bt->root, 0);
}

void print_find(BTree *tree, int key) {
	printf("Key %d found at position %d\n", key, btree_find(tree, key).index);
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
		int p = btree_find(tree, nums[i]).index;
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
	if (pos.index == -1)
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
