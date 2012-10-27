#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

namespace Btreehash
{


class node
{

public:

    long* key;
    int capacity;
    node** nodes;
    node* parent;
    long* value;
	int order;

    node ( int order ) {
        key = new long[order + 1];
        value = new long[order + 1];
        nodes = new node *[order + 2];
        capacity = 0;
        parent = NULL;
		this->order = order;
        for ( int i = 0; i <= order + 1; i++ ) {
            this->nodes[i] = NULL;
        }
    }
    ~node() {
        delete[] key;
        delete[] value;
         for ( int i = 0; i <= order + 1; i++ ) {
            delete[] nodes[i];
        }
    }

};

typedef struct node* btnode;

class btree
{

public:

    int order;
    btree ( int order ) {
        this->order = order;
    }
    void sort_array ( btnode& root ) {
        int last = root->capacity - 1;
        long tempKey, tempValue;
        for ( int i = 0; i < last; i++ ) {
            if ( root->key[last] < root->key[i] ) {
                tempKey = root->key[last];
                tempValue = root->value[last];
                for ( int j = last; j > i; j-- ) {
                    root->key[j] = root->key[j - 1];
                    root->value[j] = root->value[j - 1];
                }
                root->key[i] = tempKey;
                root->value[i] = tempValue;
                break;
            }
        }
    }

    void sort_array_with_overflow ( btnode& root ) {
        int last = root->capacity;
        root->nodes[last + 1] = root->nodes[last];
        long tempKey, tempValue;
        for ( int i = 0; i < last; i++ ) {
            if ( root->key[last] < root->key[i] ) {
                tempKey = root->key[last];
                tempValue = root->value[last];
                for ( int j = last; j > i; j-- ) {
                    root->key[j] = root->key[j - 1];
                    root->value[j] = root->value[j - 1];
                }
                root->key[i] = tempKey;
                root->value[i] = tempValue;
                break;
            }
        }
    }

    void add_middle_to_parent ( btnode& rootNode, btnode& parent, btnode left, btnode right, long middle, long value ) {
        int capacity = parent->capacity;
        int i;
        for ( i = 0; i < capacity; i++ ) {
            if ( parent->key[i] > middle )
                break;
        }
        for ( int j = capacity; j > i; j-- ) {
            parent->key[j] = parent->key[j - 1];
            parent->nodes[j + 1] = parent->nodes[j];
            parent->value[j] = parent->value[j - 1];
        }
        parent->key[i] = middle;
        parent->value[i] = value;
        parent->nodes[i] = left;
        left->parent = parent;
        parent->nodes[i + 1] = right;
        right->parent = parent;
        if ( parent->capacity < order ) {
            parent->capacity += 1;
        } else {
            split_into_children ( rootNode, parent );
        }
    }

    void split_into_children ( btnode& rootNode, btnode& root ) {
        long* key = & ( root->key[0] );
        int middle = root->capacity / 2;
        int i;
        btnode left = new node ( order );
        btnode right = new node ( order );
        btnode temp = new node ( order );
        for ( int i = 0; i < middle; i++ ) {
            left->key[i] = root->key[i];
            left->value[i] = root->value[i];
            left->capacity += 1;
            left->nodes[i] = root->nodes[i];
        }
        left->nodes[middle] = root->nodes[middle];
        for ( i = 0; i < root->capacity - middle; i++ ) {
            right->key[i] = root->key[middle + 1 + i];
            right->value[i] = root->value[middle + 1 + i];
            right->capacity += 1;
            right->nodes[i] = root->nodes[middle + 1 + i];
        }
        right->nodes[right->capacity] = root->nodes[root->capacity + 1];
        temp->key[0] = root->key[middle];
        temp->value[0] = root->value[middle];
        temp->nodes[0] = left;
        temp->nodes[1] = right;
        temp->capacity = 1;
        for ( int i = 0; i <= left->capacity; i++ ) {
            if ( left->nodes[i] != NULL )
                left->nodes[i]->parent = left;
        }
        for ( int i = 0; i <= right->capacity; i++ ) {
            if ( right->nodes[i] != NULL )
                right->nodes[i]->parent = right;
        }
        if ( root->parent == root ) {
            right->parent = temp;
            left->parent = temp;
            temp->parent = temp;
            rootNode->parent = temp;
            rootNode = temp;
        } else {
            add_middle_to_parent ( rootNode, root->parent, left, right, root->key[middle], root->value[middle] );
        }
    }

    void insert ( btnode& rootNode, btnode& root, long key, long value ) {
        if ( root != NULL && root->capacity < order && root->nodes[0] == NULL ) {
            root->key[root->capacity] = key;
            root->value[root->capacity] = value;
            root->capacity += 1;
            sort_array ( root );
        } else if ( root != NULL && root->capacity == order && root->nodes[0] == NULL ) {
            root->key[root->capacity] = key;
            root->value[root->capacity] = value;
            sort_array_with_overflow ( root );
            split_into_children ( rootNode, root );
        } else if ( root != NULL ) {
            int i;
            for ( i = 0; i < root->capacity; i++ ) {
                if ( key < root->key[i] )
                    break;
            }
            insert ( rootNode, root->nodes[i], key, value );
        } else if ( root == NULL ) {
            root = new node ( order );
            root->key[0] = key;
            root->value[0] = value;
            root->parent = root;
            root->capacity += 1;
        }
    }

    int inorder ( node* root ) {
        if ( root == NULL ) {
            return 0;
        }
        for ( int i = 0; i < root->capacity; i++ ) {
            inorder ( root->nodes[i] );
            cout << root->key[i] << " ";
            if ( i == root->capacity - 1 )
                inorder ( root->nodes[i + 1] );
        }
        return 0;
    }

    int preorder ( btnode& root ) {
        if ( root == NULL ) {
            return 0;
        }
        for ( int i = 0; i < root->capacity; i++ ) {
            cout << root->key[i] << " ";
            preorder ( root->nodes[i] );
            if ( i == root->capacity - 1 )
                preorder ( root->nodes[i + 1] );
        }
        return 0;
    }

    void level_order ( btnode& root ) {
        cout << endl;
        queue<btnode> que;
        btnode temp;
        que.push ( root );
        while ( !que.empty() ) {
            temp = que.front();
            que.pop();
            for ( int i = 0; i < temp->capacity; i++ ) {
                cout << temp->key[i]  << " ";
            }
            for ( int i = 0; i <= temp->capacity; i++ ) {
                if ( temp->nodes[i] != NULL ) {
                    que.push ( temp->nodes[i] );
                }
            }
        }
    }

    long search ( btnode& root, long key ) {
        int i;
        for ( i = 0; i < root->capacity; i++ ) {
            if ( root->key[i] == key )
                return root->key[i];
            else if ( root->key[i] > key ) {
                break;
            }
        }
        search ( root->nodes[i], key );
    }

};

class utility
{

public:
    struct hash {
        btnode* node;
    };
    long n;
    btnode root;
    btree* tree;
    long* data;
    int s;
    struct hash* hashTable;

    utility ( long n, int order, int s ) {
        this->n = n;
        this->s = s;
        root = NULL;
        data = new long[n];
        tree = new btree ( order );
        hashTable = new hash;
        hashTable->node = new node *[s];
        for ( int i = 0; i < s; i++ ) {
            hashTable->node[i] = NULL;
        }
    }

    ~utility() {
        for ( int i = 0; i < s; i++ ) {
            delete[] hashTable->node;
        }
        delete root;
        delete[] data;
        delete tree;
    }

    void generate_random() {
        long r, temp;
        long i = 0;
        data = new long[n];
        srand ( time ( 0 ) );
        while ( i < n ) {
            data[i] = i + 1;
            i++;
        }
        i = 0;
        while ( i < n / 2 ) {
            r = rand() % n;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }
    void insert_random() {
        long i = 0;
        while ( i < n ) {
            tree->insert ( hashTable->node[data[i] % s], hashTable->node[data[i] % s], data[i], 2 * data[i] );
            i++;
        }
    }

    void search_random() {
        long i = 0;
        while ( i < n ) {
            tree->search ( hashTable->node[data[i] % s], data[i] );
            i++;
        }
    }
    void inorder() {
        tree->inorder ( root );
    }
    void preorder() {
        tree->preorder ( root );
    }
    void level_order() {
        tree->level_order ( root );
    }
    void make_root_null() {
        root = NULL;
    }

    long avg ( long array[] ) {
        long sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }

    void random_runner() {
        clock_t start, end;
        long insert_array[10], search_array[10];
        cout << "Btree-hash Experiment Running....." << endl;
        for ( int i = 0; i < 10; i++ ) {
            generate_random();
            start = clock();
            insert_random();
            end = clock();
            insert_array[i] = end - start;
            start = clock();
            search_random();
            end = clock();
            search_array[i] = end - start;
            make_root_null();
        }
        delete[] data;
        cout << "Insert Avg. Time : " << avg ( insert_array ) << "   " << "Search Avg. Time : " << avg ( search_array ) << endl;
    }

};


}
