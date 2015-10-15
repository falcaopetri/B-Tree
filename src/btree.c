#include "btree.h"

BTree* btree_new(int order) {
        BTree* bt = malloc(sizeof(BTree));
        assert(bt != NULL);

        #if DEBUG
        printf("allocated new b-tree of order: %d\n", order);
        #endif

        bt->order = order;
        bt->root = node_new(order, TRUE);

        return bt;
}

node_position_t btree_find(BTree* bt, int key) {
        #if DEBUG
        printf("calling btree_find_node() over key: %d\n", key);
        #endif
        return btree_find_node (bt->root, key);
}

node_position_t btree_find_node(node_t* t, int key) {
        int i = 0;
        while (i < t->n_keys && key > t->keys[i]->key) {
                i++;
        }
        if (i < t->n_keys && key == t->keys[i]->key) {
                return node_position_new(t, i);
        }
        else if (t->is_leaf)
        {
                return node_position_new(NULL, -1);
        }
        else
        {
                return btree_find_node(t->children[i], key );
        }
}

node_position_t btree_insert(BTree* bt, int key) {
        #if DEBUG
        printf("inserting key: %d\n", key);
        #endif
        assert(bt != NULL);

        node_t *r = bt->root;

        if (r->n_keys == 2*bt->order -1) {
                #if DEBUG
                printf("node full - spliting up");
                #endif

                node_t *s = node_new(bt->order, FALSE);
                s->children[0] = r;
                bt->root = r;
                btree_split(s, 0, bt->order);
                return btree_insert_nonfull(s, key, bt->order);
        }
        else {
                #if DEBUG
                printf("root not full. calling btree_insert_nonfull()\n");
                #endif

                return btree_insert_nonfull(r, key, bt->order);
        }
}

void btree_split(node_t *x, int i, uint t)
{
        node_t *y = x->children[i];
        node_t *z = node_new(t, y->is_leaf);
        z->n_keys = t-1;
        int j;
        for(j=0; j < t-1; j++) {
                z->keys[j] = y->keys[j+t];
        }
        if(!y->is_leaf )
        {
                for(j=0; j<t; j++) {
                        z->children[j] = y->children[j+t];
                }
        }
        y->n_keys = t-1;
        for(j= x->n_keys; j> i+1; j--) {
                x->children[j+1] = x->children[j];
        }
        x->children[i+1] = z;
        for(j= x->n_keys-1; j>i; j--) {
                x->keys[j+1]=x->keys[j];
        }
        x->keys[i] = y->keys[t];
        x->n_keys = x->n_keys +1;
}

node_position_t btree_insert_nonfull(node_t * N, int k, int t) {
        #if DEBUG
        printf("at btree_insert_nonfull()\n");
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

                N->keys[i+1]->key = k;
                N->n_keys++;
                return node_position_new(N,i+1);
        }
        else{
                while(i>=0 && k<N->keys[i]->key) {
                        i--;
                }
                i++;
                if(N->children[i]->n_keys == 2*t-1)
                {
                        btree_split(N, i,t);
                        if(k > N->keys[i]->key) {
                                i++;
                        }
                }
                return btree_insert_nonfull(N->children[i], k, t);
        }
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
