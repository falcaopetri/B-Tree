#include "btree.h"

// TODO Criar diretório examples/ com arquivos de exemplos separados

void print_find(BTree *tree, int key) {
	printf("Key %d found at position %d\n", key, btree_find(tree, key).indice);
}

void print_find_n(BTree *tree, int *nums, uint n) {
	int i;
	for (i = 0; i < n; ++i) {
		print_find(tree, nums[i]);
	}
	printf("\n");
}

void print_find_assert_n(BTree *tree, int *nums, int *pos, uint n) {
	int i;
	for (i = 0; i < n; ++i) {
		int p = btree_find(tree, nums[i]).indice;
		printf("%d at %d\n", nums[i], p);
		assert(p == pos[i]);
	}
}

void print_insert(BTree *tree, int key) {
	btree_insert(tree, key);
	#if DEBUG
	printf("\n");
	#endif
}

void print_insert_n(BTree *tree, int *nums, uint n) {
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

void print_remove_n(BTree *tree, int *nums, uint n) {
	int i;
	for (i = 0; i < n; ++i) {
		print_remove(tree, nums[i]);
		printf("\n");
	}
}
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

	btree_delete(tree);

	#if DEBUG
	printf("end one_tree()\n");
	printf("\n");
	#endif
}

void multiple_trees() {
	#if DEBUG
	printf("multiple_trees()\n");
	#endif

	BTree* tree2 = btree_new(2);
	BTree* tree3 = btree_new(3);

	btree_delete(tree2);
	btree_delete(tree3);

	#if DEBUG
	printf("end multiple_trees()\n");
	printf("\n");
	#endif
}

int main() {

	one_tree();

	//multiple_trees();

	return 0;
}
