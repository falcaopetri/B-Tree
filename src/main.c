#include "btree.h"

// TODO Criar diretório examples/ com arquivos de exemplos separados

void one_tree() {
	#if DEBUG
	printf("one_tree()\n");
	#endif

	BTree* tree = btree_new(4);
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

	multiple_trees();

	return 0;
}