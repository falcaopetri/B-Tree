/*
    B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
    DC - UFSCar - São Carlos - 2015
 */
#ifndef B_TREE_TOOLS_H
#define B_TREE_TOOLS_H

#include <stdio.h>

#include "btree.h"

/*
    Executa uma DFS em node, imprimindo as chaves associadas à ele.
    Usa o parâmetro level no print dos dados do nó.
 */
void _btree_dfs_node(node_t *node, int level);
/*
    Executa uma DFS na B-Tree, imprimindo dados associados aos seus nós
    (em especial suas chaves) em ordem POSFIXA.
 */
void btree_dfs(BTree *bt);

/*
    Função para testes.
    Pesquisa a key na tree com print's para debug.
 */
void print_find(BTree *tree, int key);
/*
   Função para testes.
   Pesquisa n key's na tree com print's para debug.
 */
void print_find_n(BTree *tree, int *nums, int n);
/*
    Função para testes.
    Pesquisa n key's na tree com print's para debug
    e a verificação de que a chave nums[i] foi encontrada na posição pos[i] esperada.
 */
void print_find_assert_n(BTree *tree, int *nums, int *pos, int n);

/*
    Função para testes.
    Insere a key na tree com print's para debug
 */
void print_insert(BTree *tree, int key);
/*
    Função para testes.
    Insere n key's na tree com print's para debug
 */
void print_insert_n(BTree *tree, int *nums, int n);

/*
    Função para testes.
    Remove a key na tree com print's para debug
 */
void print_remove(BTree *tree, int key);
/*
    Função para testes.
    Remove n key's na tree com print's para debug
 */
void print_remove_n(BTree *tree, int *nums, int n);

#endif
