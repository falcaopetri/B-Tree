#ifndef B_TREE_UTIL_H
#define B_TREE_UTIL_H

#if DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <assert.h>

#include "util.h"

typedef unsigned int uint;

/*
   pair <int key, void* value>
 */
typedef struct pair_t {
        int key;
        void *value;
} pair_t;

/*
   Nó da B-Tree
   is_leaf:    esse é um nó-folha?
   n_keys:      número de chaves ativas
   level:      nível em que esse nó se encontra em relação à B-Tree

   children:   ponteiro para a lista de nós-filhos
   keys:       ponteiro para a lista de pairs (key, value)
 */
typedef struct node_t {
        bool is_leaf;
        uint n_keys;
        uint level;

        struct node_t **children;
        pair_t **keys;
} node_t;

/*
   Posição de uma key/elemento da B-Tree

   node:   ponteiro para o nó
   indice: indice da key dentro do nó
 */
typedef struct node_position_t {
        node_t *node;
        uint indice;
} node_position_t;

node_position_t node_position_new(node_t *node, uint indice);
node_t* node_new(uint order, int is_leaf);
pair_t* pair_new(int key, void *value);

#endif
