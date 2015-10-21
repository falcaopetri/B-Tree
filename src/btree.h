#ifndef B_TREE_H
#define B_TREE_H

#if DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "btree_util.h"

/*
   B-Tree
   order:  número da ordem da B-Tree (cada nó da B-Tree possui [order-1, 2*order-1] filhos)
   root:   ponteiro para o nó raiz da B-Tree ([2, 2*order-1] filhos)
 */
typedef struct btree_t {
        int order;

        node_t* root;

} BTree;


BTree* btree_new(int order);
void btree_delete(BTree *bt);

node_position btree_find(BTree* bt, int key);
node_position _btree_find_node(node_t* t, int key);
node_position btree_insert(BTree* bt, int key);
node_position btree_remove(BTree* bt, int key);
void _btree_split(node_t *x, int i, uint t);
node_position _btree_insert_nonfull(node_t * N, int k,int t);
node_position _btree_remove_node(node_t *node, int key, int order);

inline node_position _node_find_max(node_t *node);
inline node_position _node_find_min(node_t *node);

#endif
