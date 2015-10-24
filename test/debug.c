#if DEBUG
#include <stdio.h>
#endif

#include "btree.h"
#include "btree_tools.h"

void one_tree() {
	#if DEBUG
	printf("one_tree()\n");
	#endif

	BTree* tree = btree_new(2);

	int n = 6;
	int nums_insert[] = {5, 1, 10, 12, 20, 8};
	int nums_find[] = {1, 5, 8, 10, 12, 20};
	int nums_find_pos[] = {0, 0, 0, 1, 1, 0}; // btree_new(2); 6 elementos
	// int nums_find_pos[] = {0, 0, -1, 0, 1, 2}; // btree_new(2); 5 elementos
	// int nums_find_pos[] = {0, 1, -1, 2, 3, 4}; // btree_new(3); 5 elementos
	int nums_remove[] = {5, 8, 10, 12, 20, 1};

	print_insert_n(tree, nums_insert, n);
	print_find_n(tree, nums_find, n);
	print_find_assert_n(tree, nums_find, nums_find_pos, n);
	print_remove_n(tree, nums_remove, n);

	btree_delete_h(tree);

	#if DEBUG
	printf("end one_tree()\n");
	printf("\n");
	#endif
}

void stack_tree() {
	#if DEBUG
	printf("stack_tree()\n");
	#endif

	BTree tree;
	btree_init(&tree, 3);

	btree_delete_s(&tree);

	#if DEBUG
	printf("end stack_tree()\n");
	printf("\n");
	#endif
}

void multiple_trees() {
	#if DEBUG
	printf("multiple_trees()\n");
	#endif

	BTree* tree2 = btree_new(2);
	BTree* tree3 = btree_new(3);

	btree_delete_h(tree2);
	btree_delete_h(tree3);

	#if DEBUG
	printf("end multiple_trees()\n");
	printf("\n");
	#endif
}

int main() {

	one_tree();
	stack_tree();
	multiple_trees();

	return 0;
}
