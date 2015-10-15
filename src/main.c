#include "btree.h"

// TODO Criar diretório examples/ com arquivos de exemplos separados

void one_tree() {
	#if DEBUG
	printf("one_tree()\n");
	#endif

	BTree* tree = btree_new(2);

	btree_insert(tree, 5);
	#if DEBUG
	printf("\n");
	#endif
	btree_insert(tree, 1);
	#if DEBUG
	printf("\n");
	#endif
	btree_insert(tree, 10);
	#if DEBUG
	printf("\n");
	#endif
	btree_insert(tree, 20);
	#if DEBUG
	printf("\n");
	#endif
	btree_insert(tree, 12);
	#if DEBUG
	printf("\n");
	#endif
	btree_insert(tree, 8);
	#if DEBUG
	printf("\n");
	#endif

	printf("1: %d\n", btree_find(tree, 1).indice);
	printf("5: %d\n", btree_find(tree, 5).indice);
	printf("8: %d\n", btree_find(tree, 8).indice);
	printf("10: %d\n",btree_find(tree, 10).indice);
	printf("12: %d\n",btree_find(tree, 12).indice);
	printf("20: %d\n",btree_find(tree, 20).indice);
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
