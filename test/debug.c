/*
	B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
	UFSCar - São Carlos - 2015

	Define uma main() para propósitos de teste
	Executa:
		- criação na Stack
		- criação na Heap
		- criação de múltiplas árvores
		- inserção, remoção e pesquisa de chaves
	Gera um trace completo de todas as operações

	Uso:
		Compilar a B-Tree e esse arquivo com a flag DEBUG=1.
		Para tal, basta editar a variável $CFLAGS no makefile e executar:
		$ make clean
		$ make debug
		$ ./bin/debug
*/
#include <stdio.h>

#include "btree.h"
#include "btree_tools.h"

void one_tree() {
	#if DEBUG
	printf("one_tree()\n");
	#endif

	BTree* tree = btree_new(2);
	// BTree* tree = btree_new(3);

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

	#if DEBUG
	one_tree();
	stack_tree();
	multiple_trees();
	#else
	printf("Não se esqueça de compilar esse exemplo (e os arquivos da B-Tree)" \
	 		" com a flag DEBUG setada para verdadeiro: -DDEBUG=1\n");
	#endif

	return 0;
}
