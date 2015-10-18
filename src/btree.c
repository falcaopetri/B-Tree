#include "btree.h"

BTree* btree_new(int order) {
        BTree* bt = malloc(sizeof(BTree));
        assert(bt != NULL);

        #if DEBUG
        printf("allocated new b-tree of order: %d\n", order);
        #endif

        bt->order = order;
        bt->root = _node_new(order, TRUE);

        return bt;
}

node_position btree_find(BTree* bt, int key) {
        #if DEBUG
        printf("calling btree_find_node() over key: %d\n", key);
        #endif
        return _btree_find_node(bt->root, key);
}

node_position _btree_find_node(node_t* t, int key) {
        int i = 0;
        while (i < t->n_keys && key > t->keys[i]->key) {
                i++;
        }
        if (i < t->n_keys && key == t->keys[i]->key) {
                return _node_position_new(t, i);
        }
        else if (t->is_leaf) {
                return _node_position_new(NULL, -1);
        }
        else {
                return _btree_find_node(t->children[i], key );
        }
}

node_position btree_insert(BTree* bt, int key) {
        #if DEBUG
        printf("inserting key: %d\n", key);
        #endif
        assert(bt != NULL);

        node_t *r = bt->root;

        if (r->n_keys == 2*bt->order -1) {
                #if DEBUG
                printf("node full - spliting up\n");
                #endif

                node_t *s = _node_new(bt->order, FALSE);
                s->children[0] = r;
                bt->root = s;
                _btree_split(s, 0, bt->order);
                return _btree_insert_nonfull(s, key, bt->order);
        }
        else {
                #if DEBUG
                printf("root not full. calling btree_insert_nonfull()\n");
                #endif

                return _btree_insert_nonfull(r, key, bt->order);
        }
}

void _btree_split(node_t *x, int i, uint t) {
        #if DEBUG
        printf("at btree_split()\n");
        #endif

        node_t *y = x->children[i];
        assert(y != NULL);
        node_t *z = _node_new(t, y->is_leaf);
        z->n_keys = t-1;
        #if DEBUG
        printf("moving keys from root to right: ");
        #endif
        int j;
        for (j = 0; j < t-1; j++) {
                z->keys[j] = y->keys[j+t];

                #if DEBUG
                printf("%d, ", z->keys[j]->key);
                #endif
        }
        #if DEBUG
        printf("\n");
        #endif

        if (!y->is_leaf) {
                #if DEBUG
                printf("moving children from root to right: ");
                #endif
                for (j = 0; j < t; j++) {
                        z->children[j] = y->children[j+t];
                }
        }
        y->n_keys = t-1;
        #if DEBUG
        printf("deslocating new-root childrens pos: ");
        #endif
        for (j = x->n_keys; j > i+1; j--) {
                x->children[j+1] = x->children[j];
                #if DEBUG
                printf("%d, ", j);
                #endif
        }
        #if DEBUG
        printf("\n");
        #endif
        #if DEBUG
        printf("z goes to children-index %d of x\n",i+1);
        #endif

        x->children[i+1] = z;
        #if DEBUG
        printf("moving %d keys: ", x->n_keys);
        #endif
        for (j = x->n_keys-1; j > i; j--) {
                x->keys[j+1] = x->keys[j];
                #if DEBUG
                printf("%d, ", x->keys[j+1]->key);
                #endif
        }

        #if DEBUG
        printf("\n");
        #endif
        #if DEBUG
        printf("inserting key %d at %d of new-root\n", y->keys[t-1]->key, i);
        #endif
        x->keys[i] = y->keys[t-1];
        #if DEBUG
        printf("at right of new-root there is: %d\n", x->children[1]->keys[0]->key);
        #endif
        x->n_keys++;
}

node_position _btree_insert_nonfull(node_t * N, int k, int t) {
        #if DEBUG
        printf("at btree_insert_nonfull() with key %d\n", k);
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
        return _node_position_new(NULL, -1);
        //return _btree_remove_node(bt->root, key, bt->order);
}

void btree_delete(BTree *bt) {
        #if DEBUG
        printf("deleting b-tree\n");
        #endif

        // TODO update
        free(bt->root);
        free(bt);
}
