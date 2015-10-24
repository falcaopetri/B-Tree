/*
    B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
    DC - UFSCar - São Carlos - 2015
 */
#ifndef B_TREE_UTIL_H
#define B_TREE_UTIL_H

#if DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <assert.h>

#include "util.h"

/*
   pair <int key, void* value>

   Como o valor associado à chave é um ponteiro void,
   a B-Tree terá capacidade de armazenar qualquer tipo de dado
   indexável por uma chave inteira.
 */
typedef struct pair_t {
	int key;
	void *value;
} pair_t;

/*
   Nó da B-Tree
   is_leaf:    esse é um nó-folha?
   n_keys:     número de chaves ativas

   children:   ponteiro para a lista de (ponteiros para) nós-filhos
   keys:       ponteiro para a lista de (ponteiros para) pairs<key, value>
 */
typedef struct node_t {
	bool is_leaf;
	int n_keys;

	struct node_t **children;
	pair_t **keys;
} node_t;

/*
   Posição de uma key/elemento da B-Tree
   Atenção ao uso:
    Expõe acesso direto à um nó da B-Tree, incluindo suas chaves e nós-filhos

   node:    ponteiro para o nó
   index:   indice da key dentro do nó
 */
typedef struct node_position_t {
	node_t *node;
	int index;
} node_position;

/*
    Cria um novo node_position com os valores passados
 */
node_position _node_position_new(node_t *node, int index);
/*
    Aloca e retorna um novo node, com espaço para até 2*order-1 ponteiros .
    para pair's e 2*order ponteiros para node's.
    O parâmetro is_leaf é atribuído ao atributo de mesmo nome no node.
 */
node_t* _node_new(int order, bool is_leaf);
/*
    Aloca e retorna um novo pair com os valores passados.
 */
pair_t* _pair_new(int key, void *value);

/*
    Aloca e retorna um novo pair com os valores do pair passado como parâmetro
 */
inline pair_t* _pair_copy(pair_t *p);

/*
    node:   nó em que a key será pesquisada
    key:    chave à se procurar
    pos:    retorno da posição em que a chave foi encontrada. Default: -1
    @return: se a chave key pertence ou não ao nó node
 */
inline bool _node_find_key(node_t *node, int key, int* pos);

/*
    As funções a seguir correspondem à execução de um FOR.
    Tratam-se apenas de funções auxiliares para aumentar a legibilidade
    do código principal (remove_key) e precisam do contexto em que
    foram chamadas para serem compreendidas.
    O contador CONT do FOR será executado de [beg, end).

    A operação executada no FOR será:
        to.keys[padding_to + CONT] <- from.keys[padding_from + CONT]
 */
inline void _node_deslocate_keys_up(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);
inline void _node_deslocate_keys_down(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);
/*
    A operação executada no FOR será:
        to.children[padding_to + CONT] <- from.children[padding_from + CONT]
 */
inline void _node_deslocate_children_up(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);
inline void _node_deslocate_children_down(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);

/*
    Deleta um node alocado pela função _node_new(),
    isto é, essa função não tem como responsabilidade deletar
    a chaves e os nós-filhos associados à node.
 */
inline void _node_delete(node_t *node);

#endif
