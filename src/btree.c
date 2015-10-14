#include "btree.h"

BTree* btree_new(int order) { 
    BTree* bt = malloc(sizeof(BTree));
    assert(bt != NULL);

    #if DEBUG
    printf("allocated new b-tree of order: %d\n", order);
    #endif

    bt->order = order;
    bt->root = node_new(order, TRUE);
    // TODO terminar de manipular a raiz

    return bt;
}

node_position_t btree_find(BTree* bt, int key) {
    // TODO implementar

    return node_position_new(NULL, -1);
}

node_position_t btree_insert(BTree* bt, int key) {
    // TODO implementar

    return node_position_new(NULL, -1);
}

node_position_t btree_remove(BTree* bt, int key) {
    // TODO implementar

    return node_position_new(NULL, -1);
}

void btree_delete(BTree *bt) {
    #if DEBUG
    printf("deleting b-tree\n");
    #endif

    // TODO update
    free(bt->root);
    free(bt);
}