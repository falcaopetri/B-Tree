#include "btree.h"

BTree* btree_new(int order) {
        BTree* bt = malloc(sizeof(BTree));
        assert(bt != NULL);

        #if DEBUG
        printf("allocated new b-tree of order %d\n", order);
        #endif

        bt->order = order;
        bt->root = _node_new(order, TRUE);
        // TODO bt->root == NULL

        return bt;
}

node_position btree_find(BTree* bt, int key) {
        #if DEBUG
        printf("calling _btree_find_node() over key: %d\n", key);
        #endif
        return _btree_find_node(bt->root, key);
}

node_position _btree_find_node(node_t* node, int key) {
        int pos;
        if (_node_find_key(node, key, &pos)) {
                return _node_position_new(node, pos);
        }
        else {
            if (node->is_leaf) {
                return _node_position_new(NULL, -1);
            }
            else {
                return _btree_find_node(node->children[pos], key);
            }
        }
}

node_position btree_insert(BTree* bt, int key) {
        assert(bt != NULL);

        #if DEBUG
        printf("inserting key %d\n", key);
        #endif

        node_t *root = bt->root;

        if (root->n_keys == 2*bt->order -1) {
                #if DEBUG
                printf("root full - spliting up\n");
                #endif

                node_t *new_root = _node_new(bt->order, FALSE);
                new_root->children[0] = root;

                _btree_split(new_root, 0, bt->order);
                bt->root = new_root;

                return _btree_insert_nonfull(new_root, key, bt->order);
        }
        else {
                #if DEBUG
                printf("root not full - calling _btree_insert_nonfull()\n");
                #endif

                return _btree_insert_nonfull(root, key, bt->order);
        }
}

void _btree_split(node_t *x, int i, uint t) {
        node_t *y = x->children[i];
        assert(y != NULL);

        node_t *z = _node_new(t, y->is_leaf);
        z->n_keys = t-1;
        #if DEBUG
        printf("moving keys from root to right: ");
        #endif
        _node_deslocate_keys_up(z, y, 0, t-1, 0, t);
        // int j;
        // for (j = 0; j < t-1; j++) {
        //         z->keys[j] = y->keys[j+t];
        //
        //         #if DEBUG
        //         printf("%d, ", z->keys[j]->key);
        //         #endif
        // }
        #if DEBUG
        printf("\n");
        #endif

        if (!y->is_leaf) {
                #if DEBUG
                printf("moving children from root to right: ");
                #endif
                _node_deslocate_children_up(z, y, 0, t, 0, t);
                // for (j = 0; j < t; j++) {
                //         z->children[j] = y->children[j+t];
                // }
        }
        y->n_keys = t-1;

        #if DEBUG
        printf("deslocating new-root childrens pos: ");
        #endif

        _node_deslocate_children_down(x, x, x->n_keys, i+1, 1, 0);
        // for (j = x->n_keys; j > i+1; j--) {
        //         x->children[j+1] = x->children[j];
        //         #if DEBUG
        //         printf("%d, ", j);
        //         #endif
        // }
        #if DEBUG
        printf("\n");
        #endif

        x->children[i+1] = z;
        #if DEBUG
        printf("moving %d keys: ", x->n_keys);
        #endif
        _node_deslocate_keys_down(x, x, x->n_keys-1, i, 1, 0);
        // for (j = x->n_keys-1; j > i; j--) {
        //         x->keys[j+1] = x->keys[j];
        //         #if DEBUG
        //         printf("%d, ", x->keys[j+1]->key);
        //         #endif
        // }

        #if DEBUG
        printf("\n");
        #endif
        #if DEBUG
        printf("inserting key %d at %d of new-root\n", y->keys[t-1]->key, i);
        #endif
        x->keys[i] = y->keys[t-1];
        // TODO o que acontece com "y->keys[t-1]"??
        #if DEBUG
        printf("at right of new-root there is: %d\n", x->children[1]->keys[0]->key);
        #endif
        x->n_keys++;
}

node_position _btree_insert_nonfull(node_t * N, int k, int t) {
        #if DEBUG
        printf("at _btree_insert_nonfull() with key %d\n", k);
        #endif

        int i = N->n_keys -1;
        if (N->is_leaf)   {
                #if DEBUG
                printf("at leaf node\n");
                #endif

                while (i >= 0 && k < N->keys[i]->key) {
                        N->keys[i+1] = N->keys[i];
                        i--;
                }

                N->keys[i+1] = _pair_new(k, NULL);
                N->n_keys++;
                #if DEBUG
                printf("inserted key %d at position %d\n", k, i+1);
                #endif
                return _node_position_new(N,i+1);
        }
        else {
                while(i>=0 && k<N->keys[i]->key) {
                        i--;
                }
                i++;
                if(N->children[i]->n_keys == 2*t-1)
                {
                        _btree_split(N, i,t);
                        if(k > N->keys[i]->key) {
                                i++;
                        }
                }
                return _btree_insert_nonfull(N->children[i], k, t);
        }
}

node_position btree_remove(BTree* bt, int key) {
        assert(bt != NULL);
        node_position pos = _btree_remove_node(bt->root, key, bt->order);
        if (bt->root->n_keys == 0 && pos.node != bt->root) {
            #if DEBUG
            printf("BTree root became empty. New root will be its left child\n");
            #endif
            bt->root = bt->root->children[0];
            printf("DDD: %d\n", bt->root->n_keys);
        }

        return pos;
}

node_position _btree_remove_node(node_t *node, int key, int order) {
        #if DEBUG
        printf("at btree_remove_node() to remove key %d\n", key);
        #endif
        int pos;

        if (_node_find_key(node, key, &pos)) {
                #if DEBUG
                printf("found %d at pos %d\n", key, pos);
                #endif
                if (node->is_leaf) {
                        /*
                            Caso 1: Se a chave k está em um nó x e x é uma
                            folha, remova a chave k de x
                         */
                        #if DEBUG
                        printf("case 1. node is leaf. removing.\n");
                        #endif
                        free(node->keys[pos]);
                        node->n_keys--;
                        _node_deslocate_keys_up(node, node, pos, node->n_keys, 0, 1);
                        // int j;
                        // for (j = pos; j < node->n_keys; ++j) {
                        //         node->keys[j] = node->keys[j+1];
                        // }

                        return _node_position_new(node, pos);
                }
                else {
                        /*
                            Caso 2: Se a chave k está em um nó x e x é um nó
                            interno.
                         */
                        node_t *left = node->children[pos];
                        node_t *right = node->children[pos+1];
                        if (left->n_keys >= order) {
                                /*
                                    a) Se o nó filho y que precede k no nó x
                                    tem pelo menos t chaves, encontre o
                                    predecessor k’ de k na subárvore
                                    enraizada em y.
                                    Remova k’, e substitua k por k’ em x.
                                */
                                #if DEBUG
                                printf("case 2a. left sibling has %d keys.\n", left->n_keys);
                                #endif
                                free(node->keys[pos]);

                                node_position max = _node_find_max(left);
                                node->keys[pos] = _pair_copy(left->keys[max.indice]);

                                _btree_remove_node(left, node->keys[pos]->key, order);
                                return _node_position_new(node, pos);
                        }
                        else if (right->n_keys >= order) {
                                /*
                                    Caso simétrico ao 2a. Se o nó filho y que
                                    precede k no nó x tem menos que t chaves,
                                    examine o nó filho z que vem depois de
                                    k no nó x.
                                 */

                                #if DEBUG
                                printf("case 2b. right sibling has %d keys.\n", right->n_keys);
                                #endif

                                #if DEBUG
                                printf("deleting key %d\n", node->keys[pos]->key);
                                #endif
                                free(node->keys[pos]);

                                node_position min = _node_find_min(right);
                                node->keys[pos] = _pair_copy(right->keys[min.indice]);

                                _btree_remove_node(right, node->keys[pos]->key, order);
                                return _node_position_new(node, pos);
                        }
                        else {
                                /*
                                    2c) Se ambos os nós filhos y e z possuem
                                    apenas t-1 chaves, concatena-se k e todo o
                                    conteúdo de z com y, de maneira que x perca
                                    a chave k e o ponteiro para z
                                 */
                                #if DEBUG
                                printf("case 2c\n");
                                #endif

                                left->keys[order-1] = node->keys[pos];

                                _node_deslocate_keys_up(left, right, 0, order-1, order, 0);
                                // int j;
                                // for (j = 0; j < order-1; ++j) {
                                //         //left->keys[order+j] = _pair_copy(right->keys[j]);
                                //         left->keys[order+j] = right->keys[j];
                                //         // TODO precisa dar free?
                                //         //free(right->keys[j]);
                                // }

                                _node_deslocate_children_up(left, right, 0, order, order, 0);
                                // for (j = 0; j < order; ++j) {
                                //         left->children[order+j] = right->children[j];
                                // }
                                left->n_keys = 2*order - 1;

                                _node_delete(right);
                                // free(right->children);
                                // free(right->keys);
                                // free(right);

                                _node_deslocate_keys_up(node, node, pos, node->n_keys-1, 0, 1);
                                // for (j = pos; j < node->n_keys-1; ++j) {
                                //     node->keys[j] = node->keys[j+1];
                                // }

                                _node_deslocate_children_up(node, node, pos, node->n_keys-1, 1, 2);
                                // for (j = pos; j < node->n_keys-1; ++j) {
                                //     node->children[j+1] = node->children[j+2];
                                // }
                                node->n_keys--;

                                return _btree_remove_node(left, key, order);
                        }
                }
        }
        else {
                // TODO next == left
                node_t *next = node->children[pos];

                if (next->n_keys == order-1) {
                        node_t *left = node->children[pos];
                        node_t *right = node->children[pos+1];

                        if (left->n_keys >= order) {
                                // TODO
                                node_position max = _node_find_max(left);
                                pair_t* p = left->keys[max.indice];

                                // swap(left->keys[max.indice], node->keys[i], sizeof(node->keys[i]));
                                // swap(left->children[max.indice], node->children[i], sizeof(node->children[i]));

                                return _btree_remove_node(left, key, order);
                        }
                        else if (right->n_keys >= order) {
                                // TODO
                                node_position min = _node_find_min(right);
                                pair_t* p = right->keys[min.indice];
                                // swap(right->keys[min.indice], node->keys[i], sizeof(node->keys[i]));
                                // swap(right->children[min.indice], node->children[i], sizeof(node->children[i]));

                                return _btree_remove_node(right, key, order);
                        }
                        else {
                                left->keys[order-1] = node->keys[pos];
                                // left->keys[order-1] = _pair_copy(node->keys[pos]);
                                // free(node->keys[pos]);

                                _node_deslocate_keys_up(node, node, pos, node->n_keys-1, 0, 1);
                                // int j;
                                // for (j = pos; j < node->n_keys-1; ++j) {
                                //     node->keys[j] = node->keys[j+1];
                                // }
                                _node_deslocate_children_up(node, node, pos, node->n_keys-1, 1, 2);
                                // for (j = pos; j < node->n_keys-1; ++j) {
                                //     node->children[j+1] = node->children[j+2];
                                // }

                                node->n_keys--;

                                _node_deslocate_keys_up(left, right, 0, order-1, order, 0);
                                // for (j = 0; j < order-1; ++j) {
                                //         //left->keys[order+j] = _pair_copy(right->keys[j]);
                                //         left->keys[order+j] = right->keys[j];
                                //         // TODO precisa dar free
                                //         free(right->keys[j]);
                                // }
                                _node_deslocate_children_up(left, right, 0, order, 0, 0);
                                // for (j = 0; j < order; ++j) {
                                //         left->children[order+j] = right->children[j];
                                // }
                                _node_delete(right);
                                // free(right->children);
                                // free(right->keys);
                                // free(right);

                                return _btree_remove_node(left, key, order);
                        }
                }

                return _btree_remove_node(next, key, order);
        }
}

void btree_delete(BTree *bt) {
        #if DEBUG
        printf("deleting b-tree\n");
        #endif

        // TODO make this efficient
        while (bt->root->n_keys > 0) {
            btree_remove(bt, bt->root->keys[0]->key);
        }

        free(bt->root);
        free(bt);
}
