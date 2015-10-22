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
 */
typedef struct pair_t {
    int key;
    void *value;
} pair_t;

/*
   Nó da B-Tree
   is_leaf:    esse é um nó-folha?
   n_keys:     número de chaves ativas

   children:   ponteiro para a lista de nós-filhos
   keys:       ponteiro para a lista de pairs (key, value)
 */
typedef struct node_t {
    bool is_leaf;
    uint n_keys;

    struct node_t **children;
    pair_t **keys;
} node_t;

/*
   Posição de uma key/elemento da B-Tree
   Expõe acesso direto à um nó da B-Tree, incluindo suas chaves e nós-filhos

   node:   ponteiro para o nó
   indice: indice da key dentro do nó
 */
typedef struct node_position_t {
    node_t *node;
    uint indice;
} node_position;

node_position _node_position_new(node_t *node, uint indice);
node_t* _node_new(uint order, bool is_leaf);
pair_t* _pair_new(int key, void *value);

inline pair_t* _pair_copy(pair_t *p);

inline bool _node_find_key(node_t *node, int key, int* pos);

inline void _node_deslocate_keys_up(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);
inline void _node_deslocate_keys_down(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);

inline void _node_deslocate_children_up(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);
inline void _node_deslocate_children_down(node_t *to, node_t *from, int beg, int end, int padding_to, int padding_from);

inline void _node_delete(node_t *node);

#endif
