#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

namespace Btree
{

class node
{
public:
    long* key;
    int capacity;
    node** nodes;
    node* parent;
    long* value;

    node ( int order ) {
        key = new long[order + 1];
        value = new long[order + 1];
        nodes = new node *[order + 2];
        capacity = 0;
        parent = NULL;
        for ( int i = 0; i <= order + 1; i++ ) {
            this->nodes[i] = NULL;
        }
    }

    ~node() {
        delete[] key;
        delete[] value;
        delete[] nodes;
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
                    //root->nodes[j+1] = root->nodes[j];
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
                    //root->nodes[j+1] = root->nodes[j];
                    root->value[j] = root->value[j - 1];
                }
                root->key[i] = tempKey;
                root->value[i] = tempValue;
                break;
            }
        }
    }

    void add_middle_to_parent ( btnode& rootNode, btnode& parent, btnode left, btnode right, long middle, long value ) {
        //cout << "In add middle to parent" << endl;
        //cout << "middle element = " << middle << endl;
        //cout << "In middle + Capacity = " << parent->capacity << endl;
        int capacity = parent->capacity;
        int i;
        for ( i = 0; i < capacity; i++ ) {
            if ( parent->key[i] > middle )
                break;
        }
        //cout << "outside first for" << endl;
        for ( int j = capacity; j > i; j-- ) {
            parent->key[j] = parent->key[j - 1];
            parent->nodes[j + 1] = parent->nodes[j];
            parent->value[j] = parent->value[j - 1];
            //cout << "= " << parent->key[j] << " ";
        }
        //cout << endl;
        //cout << "done finding index" << endl;
        parent->key[i] = middle;
        parent->value[i] = value;
        parent->nodes[i] = left;
        left->parent = parent;
        parent->nodes[i + 1] = right;
        right->parent = parent;
        //cout << "done setting parent" << endl;
        if ( parent->capacity < order ) {
            //cout << "setting parent capacity" << endl;
            parent->capacity += 1;
            //  cout << "done setting parent capacity" << endl;
            //  cout << "Capacity = " << parent->capacity << endl;
        } else {
            split_into_children ( rootNode, parent );
        }
    }

    void split_into_children ( btnode& rootNode, btnode& root ) {
        //btnode *root = rootx;
        //cout << "In split into  children" << endl;
        long* key = & ( root->key[0] );
        //cout << "key = " << root->key[1] << endl;
        int middle = root->capacity / 2;
        int i;
        //cout << "middle element = " << root->key[middle] << endl;
        btnode left = new node ( order );
        btnode right = new node ( order );
        btnode temp = new node ( order );
        for ( int i = 0; i < middle; i++ ) {
            left->key[i] = root->key[i];
            left->value[i] = root->value[i];
            left->capacity += 1;
            left->nodes[i] = root->nodes[i];
            //cout << "key = " << left->key[i] << endl;
            //cout << "Capacity = " << left->capacity << endl;
        }
        left->nodes[middle] = root->nodes[middle];
        for ( i = 0; i < root->capacity - middle; i++ ) {
            right->key[i] = root->key[middle + 1 + i];
            right->value[i] = root->value[middle + 1 + i];
            right->capacity += 1;
            right->nodes[i] = root->nodes[middle + 1 + i];
            //cout << "key = " << right->key[i] << endl;
        }
        right->nodes[right->capacity] = root->nodes[root->capacity + 1];
        //right->key[right->capacity] = root->key[root->capacity];
        //right->capacity += 1;
        //cout << "Right Capacity = " << right->capacity << endl;
        //cout << "Right Element = " << right->key[0] << endl;
        //cout << "leftest element = " << (root->key[0]) << endl;
        //cout << "rightest element = " << (root->key[root->capacity]) << endl;
        temp->key[0] = root->key[middle];
        temp->value[0] = root->value[middle];
        temp->nodes[0] = left;
        temp->nodes[1] = right;
        temp->capacity = 1;
        for ( int i = 0; i <= left->capacity; i++ ) {
            if ( left->nodes[i] != NULL )
                left->nodes[i]->parent = left;
        }
        //cout << "Right Capacity = " << right->capacity << " " << right->key[0] << endl;
        for ( int i = 0; i <= right->capacity; i++ ) {
            if ( right->nodes[i] != NULL )
                right->nodes[i]->parent = right;
        }
        //cout << "left key = " << temp->nodes[0]->key[0] << endl;
        //cout << "right key = " << temp->nodes[1]->key[0] << endl;
        //cout << "In split to children -- Capacity = " << root->parent->capacity << endl;
        //error - root pointer is not modified correctly
        if ( root->parent == root ) {
            right->parent = temp;
            left->parent = temp;
            temp->parent = temp;
            rootNode->parent = temp;
            rootNode = temp;
            //cout << "In root" << endl;
            //cout << "root key = " << root->key[0] << endl;
            //  cout << "Capacity = " << temp->capacity << endl;
        } else {
            //  cout << "parent capacity = " << root->parent->capacity << endl;
            add_middle_to_parent ( rootNode, root->parent, left, right, root->key[middle], root->value[middle] );
        }
    }



    void insert ( btnode& rootNode, btnode& root, long key, long value ) {
        //cout << "++++++++++++++++++++inserting+++++++++++++++++++++++ " << key << endl;
        //btnode *root = rootx;
        //cout << "Order = " << order << endl;
        //cout << "parent Capacity = " << root->parent->capacity << endl;
        if ( root != NULL && root->capacity < order && root->nodes[0] == NULL ) {
            //cout << "Capacity = " << root->capacity << endl;
            //cout << "insert in same node" << endl;
            root->key[root->capacity] = key;
            root->value[root->capacity] = value;
            root->capacity += 1;
            //  cout << "Capacity = " << root->capacity << endl;
            sort_array ( root );
        } else if ( root != NULL && root->capacity == order && root->nodes[0] == NULL ) {
            //cout << "Capacity = " << root->capacity << endl;
            //cout << "In split" << endl;
            //cout << "parent Capacity = " << root->parent->capacity  << " " << root->parent->key[0] << " " << root->key[0] << endl;
            root->key[root->capacity] = key;
            root->value[root->capacity] = value;
            sort_array_with_overflow ( root );
            //cout << endl;
            split_into_children ( rootNode, root );
        } else if ( root != NULL ) {
            //cout << "insert in child node" << endl;
            //cout << "Capacity = " << root->capacity << endl;
            int i;
            for ( i = 0; i < root->capacity; i++ ) {
                if ( key < root->key[i] )
                    break;
            }
            insert ( rootNode, root->nodes[i], key, value );
        } else if ( root == NULL ) {
            //cout << "new node" << endl;
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
            //cout << "going left" << endl;
            inorder ( root->nodes[i] );
            //cout << "printing key" << endl;
            cout << root->key[i] << " ";
            //cout << "going right" << endl;
            if ( i == root->capacity - 1 )
                inorder ( root->nodes[i + 1] );
        }
        //inorder(root->nodes[root->capacity]);
        return 0;
    }

    int preorder ( btnode& root ) {
        //btnode *root = rootx;
        //cout << "In inorder" << endl;
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
        //  cout << "LEVEL OREDER TRAVERSAL STARTED" << endl;
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
            //cout << endl;
            for ( int i = 0; i <= temp->capacity; i++ ) {
                if ( temp->nodes[i] != NULL ) {
                    que.push ( temp->nodes[i] );
                }
            }
        }
        //cout << "LEVEL OREDER TRAVERSAL ENDED" << endl;
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
    long n;
    btnode root;
    btree* tree;
    long* data;

    utility ( long n, int order ) {
        this->n = n;
        root = NULL;
        data = new long[n];
        tree = new btree ( order );
    }

    void generate_random() {
        //cout << n << endl;
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
            //cout << r << "->" << i << endl;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }

    void insert_random() {
        long i = 0;
        while ( i < n ) {
            //cout << "Inserting = " << data[i] <<  endl;
            tree->insert ( root, root, data[i], 2 * data[i] );
            i++;
        }
    }

    void generate_increasing() {
        long int i = 0;
        while ( i < n ) {
            data[i] = i + 1;
            //cout << data[n-i] << " ";
            i++;
        }
        //cout << endl;
    }

    void search_random() {
        long i = 0;
        while ( i < n ) {
            tree->search ( root, data[i] );
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

    void print_root() {
        cout << root->key[0] << endl;
    }

    void random_runner() {
        clock_t start, end;
        long insert_array[10], search_array[10];
        cout << "Btree Experiment Running....." << endl;
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
        delete root;
        delete tree;
        cout << "Insert Avg. Time : " << avg ( insert_array ) << "   " << "Search Avg. Time : " << avg ( search_array ) << endl;
    }
};

}

