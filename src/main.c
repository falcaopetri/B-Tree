#include "btree.h"

// TODO Criar diretório examples/ com arquivos de exemplos separados

void one_tree() {
	#if DEBUG
	printf("one_tree()\n");
	#endif

	BTree* tree = btree_new(4);

	btree_insert(tree, 5);
	btree_insert(tree, 1);
	/*btree_insert(tree, 10);
	btree_insert(tree, 20);
	btree_insert(tree, 12);
	btree_insert(tree, 8);*/

	node_position_t A = btree_find(tree, 5);
	// node_position_t B = btree_find(tree, 2);
	printf("%d\n", A.indice);
	// printf("%d\n",B.indice);
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
