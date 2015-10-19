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


	int nums_insert[] = {5, 1, 10, 12, 20, 8};
	int nums_find[] = {1, 5, 8, 10, 12, 20};
	int nums_remove[] = {5, 8, 10, 12, 20, 1};

	print_insert_n(tree, nums_insert, 6);
	print_find_n(tree, nums_find, 6);
	print_remove_n(tree, nums_remove, 6);

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
