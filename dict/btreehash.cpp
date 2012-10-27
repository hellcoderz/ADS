#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

namespace Btreehash
{


//node structure for b+ tree node
class node
{
public:
    long* key;  //array of keys
    int capacity;   //to hold # of elements in that node
    node** nodes;   //array of child pointers
    node* parent;   //pointer to point to parent node
    long* value;    //array of values
    int order;  //to store order of b+ tree
    //constructor
    node ( int order ) {
        key = new long[order + 1];  //allocating memory for keys
        value = new long[order + 1];    //allocating memory for values
        nodes = new node *[order + 2];  //allocating memory for child pointers
        capacity = 0;   // setting initial # of elements
        this->order = order;    //
        parent = NULL;
        for ( int i = 0; i <= order + 1; i++ ) {
            this->nodes[i] = NULL;
        }
    }
    //destructor to deallocate memory
    ~node(){
        delete[] key;
        delete[] value;
        for ( int i = 0; i <= order + 1; i++ ) {
            if(nodes[i] != NULL)
                delete nodes[i];
        }
        
    }

};

typedef struct node* btnode;    //alias for node*

//b+ tree class containing all functions that can be performed on b+ tree
class btree
{
public:
    int order;
    btnode left, right, temp;
    btree ( int order ) {
        this->order = order;
        left = NULL;
        right = NULL;
        temp = NULL;
    }

    ~btree(){
        delete left;
        delete right;
        delete temp;
    }

    //sorting the elements when there is no qverflow of elements
    void sort_array ( btnode& root ) {
        int last = root->capacity - 1;
        long tempKey, tempValue;
        for ( int i = 0; i < last; i++ ) {  //loop to find position where we have to insert the last element
            if ( root->key[last] < root->key[i] ) {
                tempKey = root->key[last];
                tempValue = root->value[last];
                for ( int j = last; j > i; j-- ) {  //loop to shift keys and value 
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
    //sorting the elements when there is an overflow element
    void sort_array_with_overflow ( btnode& root ) {
        int last = root->capacity;
        root->nodes[last + 1] = root->nodes[last];
        long tempKey, tempValue;
        for ( int i = 0; i < last; i++ ) {  //loop to find position where we have to insert the overflow element
            if ( root->key[last] < root->key[i] ) {
                tempKey = root->key[last];
                tempValue = root->value[last];
                for ( int j = last; j > i; j-- ) {  //loop to shift keys and value 
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
    //function to add the new tree created when node is overflowed in the parent node
    void add_middle_to_parent ( btnode& rootNode, btnode parent, btnode left, btnode right, long middle, long value ) {
       //cout << "In add middle to parent" << endl;
        //cout << "middle element = " << middle << endl;
        //cout << "In middle + Capacity = " << parent->capacity << endl;
        
        //check if parent is null
        if(parent == NULL)
            cout << "parent null" << endl;
        int capacity = parent->capacity;
        int i;
        //find the position where we have to insert the new tree
        for ( i = 0; i < capacity; i++ ) {
            if ( parent->key[i] > middle )
                break;
        }
        //cout << "outside first for" << endl;
        //shift all the elements to make space for the new tree
        for ( int j = capacity; j > i; j-- ) {
            parent->key[j] = parent->key[j - 1];
            parent->nodes[j + 1] = parent->nodes[j];
            parent->value[j] = parent->value[j - 1];
            //cout << "= " << parent->key[j] << " ";
        }
        //cout << endl;
        //cout << "done finding index" << endl;
        //add the element int the parent node
        parent->key[i] = middle;
        parent->value[i] = value;
        parent->nodes[i] = left;
        left->parent = parent;
        parent->nodes[i + 1] = right;
        right->parent = parent;
        //cout << "done setting parent" << endl;
        //check if parent can hold the new tree
        if ( parent->capacity < order ) {
            //cout << "setting parent capacity" << endl;
            parent->capacity += 1;
            //  cout << "done setting parent capacity" << endl;
            //  cout << "Capacity = " << parent->capacity << endl;
        } else {
            //if the parent node cant hod the new tree so split this node also
            split_into_children ( rootNode, parent );
        }
    }
    //split node beacuse it has reached its amximum capacity
    void split_into_children ( btnode& rootNode, btnode &root ) {
        //btnode *root = rootx;
        //cout << "In split into  children" << endl;
        long* key = & ( root->key[0] );
        //cout << "key = " << root->key[1] << endl;
        int middle = root->capacity / 2;
        int i;
        //allocate space for 3 node tree
        left = new node ( order );
        right = new node ( order );
        temp = new node ( order );
        // copy all the information of the elements present on the left side of the middle element
        for ( int i = 0; i < middle; i++ ) {
            left->key[i] = root->key[i];
            left->value[i] = root->value[i];
            left->capacity += 1;
            left->nodes[i] = root->nodes[i];
            //cout << "key = " << left->key[i] << endl;
            //cout << "Capacity = " << left->capacity << endl;
        }
        left->nodes[middle] = root->nodes[middle];

        // copy all the information of the elements present on the right side of the middle element
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

        //copy the information of the middle element in the root of this small tree
        temp->key[0] = root->key[middle];
        temp->value[0] = root->value[middle];
        temp->nodes[0] = left;
        temp->nodes[1] = right;
        temp->capacity = 1;

        //set parent node for left node children
        for ( int i = 0; i <= left->capacity; i++ ) {
            if ( left->nodes[i] != NULL )
                left->nodes[i]->parent = left;
        }
        //cout << "Right Capacity = " << right->capacity << " " << right->key[0] << endl;
        //set parent node for left node children
        for ( int i = 0; i <= right->capacity; i++ ) {
            if ( right->nodes[i] != NULL )
                right->nodes[i]->parent = right;
        }
        //cout << "left key = " << temp->nodes[0]->key[0] << endl;
        //cout << "right key = " << temp->nodes[1]->key[0] << endl;
        //cout << "In split to children -- Capacity = " << root->parent->capacity << endl;
        //error - root pointer is not modified correctly
        //check if this is the root node of the btree
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
              //cout << "parent capacity = " << root->parent->capacity << endl;
            //if its not root node then add the new tree to the parent node
            add_middle_to_parent ( rootNode, root->parent, left, right, root->key[middle], root->value[middle] );
        }
    }


    //function to perform insertion of key and value in b+ tree through recursion
    void insert ( btnode& rootNode, btnode& root, long key, long value ) {
        //cout << "++++++++++++++++++++inserting+++++++++++++++++++++++ " << key << endl;
        //btnode *root = rootx;
        //cout << "Order = " << order << endl;
        //cout << "parent Capacity = " << root->parent->capacity << endl;
        //check if node can hold the new element
        if ( root != NULL && root->capacity < order && root->nodes[0] == NULL ) {
            //cout << "Capacity = " << root->capacity << endl;
            //cout << "insert in same node" << endl;
            root->key[root->capacity] = key;
            root->value[root->capacity] = value;
            root->capacity += 1;
            //  cout << "Capacity = " << root->capacity << endl;
            sort_array ( root ); //sort the node after adding the new element

            //check if node cannot hold the new element and split the node
        } else if ( root != NULL && root->capacity == order && root->nodes[0] == NULL ) {
            //cout << "Capacity = " << root->capacity << endl;
            //cout << "In split" << endl;
            //cout << "parent Capacity = " << root->parent->capacity  << " " << root->parent->key[0] << " " << root->key[0] << endl;
            root->key[root->capacity] = key;    //add element key at the exatr space in the the last
            root->value[root->capacity] = value;    //add element key at the exatr space in the the last
            sort_array_with_overflow ( root );      //sort the node with this new extra node
            //cout << endl;
            split_into_children ( rootNode, root ); //split the node

            //check which subtree will hold the new element
        } else if ( root != NULL ) {
            //cout << "insert in child node" << endl;
            //cout << "Capacity = " << root->capacity << endl;
            int i;
            for ( i = 0; i < root->capacity; i++ ) {
                if ( key < root->key[i] )
                    break;
            }
            insert ( rootNode, root->nodes[i], key, value );    // insert the new element in this subtree

            //check if this is the first element in the b+ tree and add a new node;
        } else if ( root == NULL ) {
            //cout << "new node" << endl;
            root = new node ( order );
            root->key[0] = key;
            root->value[0] = value;
            root->parent = root;
            root->capacity += 1;
        }
    }

    //print inorder traversal of the tree
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
    //print preorder traversal of the tree
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
    //print level order traversal of the tree
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
    //function to search key in the b+ tree
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
            //cout << "inserting = " << data[i] << endl;
            tree->insert ( hashTable->node[data[i] % s], hashTable->node[data[i] % s], data[i], 2 * data[i] );
            //cout << endl;
            //inorder();
            //cout << endl;
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
        //cout << "Experiment Running....." << endl;
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
        cout << avg ( insert_array ) << " " <<  avg ( search_array ) << endl;    
    }

};


}

//driver function

int main()
{
    long n = 1000000;
    int order = 50;
    int s = 101;
    Btreehash::utility* util = new Btreehash::utility ( n, order - 1, s );
    util->random_runner();
    return 0;
}