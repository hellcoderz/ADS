#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>
using namespace std;


namespace AVLhash
{

#define CHECK_BALANCE
#define PAIR(x,y) pair<long,node*>(x,y)


// node structure of avltree
class node
{
public:
    long key;   //node key
    long value; //node value
    node* left; //left child
    node* right;    //right child
    int height; //height of the tree i.e. max height from left or right subtree
};

typedef struct node avlNode;    //just an alias

// avlhash tree class containing all functions of the tree
class avlTree
{
public:
    // hashmap to store s no. of of trees
    struct hash {
        avlNode** node;
    };


    int s;
    struct hash* hashTable;
    // constructor
    avlTree ( int s ) {
        this->s = s;
        hashTable = new hash; // allocating space for hash table
        hashTable->node = new node *[s]; // allocating space for s avl trees
        for ( int i = 0; i < s; i++ ) {
            hashTable->node[i] = NULL;  // making all roots NULL of each avltree
        }
    }

    //absoulute value function
    int abs ( int n ) {
        if ( n < 0 )
            return -n;
        else
            return n;
    }
    // function to find max of the two numbers
    int max ( int a, int b ) {
        if ( a > b )
            return a;
        else
            return b;
    }
    //function to the height of that node in the avltree
    int height ( avlNode* root ) {
        if ( root == NULL )
            return 0;
        return root->height;
    }
    // function to perform right rotation
    avlNode* rotateRight ( avlNode* root ) {
        //cout << "Rotate Right" << endl;
        avlNode* temp = root->left;
        root->left = NULL;
        if ( temp->right != NULL ) {
            root->left = temp->right;
        }
        // Perform rotation
        temp->right = root;
        // Update heights
        root->height = max ( height ( root->left ), height ( root->right ) ) + 1;
        temp->height = max ( height ( temp->left ), height ( temp->right ) ) + 1;
        // Return new root
        return temp;
    }
    //function to perform left rotation
    avlNode* rotateLeft ( avlNode* root ) {
        //cout << "Rotate Left: " << root->key << endl;
        avlNode* temp = root->right;
        root->right = NULL;
        //cout << "temp->key = " << root->key << endl;
        if ( temp->left != NULL ) {
            root->right = temp->left;
        }
        // Perform rotation
        temp->left = root;
        // Update heights
        root->height = max ( height ( root->left ), height ( root->right ) ) + 1;
        temp->height = max ( height ( temp->left ), height ( temp->right ) ) + 1;
        // Return new root
        return temp;
    }

    // function to insert key and values in the avl tree
    avlNode* insert_data ( avlNode* node, long int key, long int value ) {
        avlNode* temp;

        //condition when tree is subtree is empty and new node can be inserted here
        if ( node == NULL ) {
            //cout << "Insert: " << key << endl;
            node = new avlNode;
            node->left = NULL;
            node->right = NULL;
            node->key = key;
            node->value = value;
            node->height = 1;
            temp = node;

            //condition to check if key should be added in the left subtree
        } else {
            if ( node->key > key ) {
                node->left = insert_data ( node->left, key, value );
                temp = node;

                //condition to check if key should be added in the right subtree
            } else {
                node->right = insert_data ( node->right, key, value );
                temp = node;
            }
        }

        // update height of the parent node
        temp->height = max ( height ( temp->left ), height ( temp->right ) ) + 1;
        //calculate the balance height of the parent node
        int balance = height ( temp->left ) - height ( temp->right );
        // If this node becomes unbalanced, then there are 4 cases
        //cout << "Current root = " << temp->key <<  " " << "balance = " << balance << endl;
        // Left Left Case
        if ( balance > 1 && temp->left != NULL && key < temp->left->key )
            temp = rotateRight ( temp );
        // Right Right Case
        else if ( balance < -1 && temp->right != NULL && key > temp->right->key )
            temp = rotateLeft ( temp );
        // Left Right Case
        else if ( balance > 1 && temp->left != NULL && key > temp->left->key ) {
            temp->left = rotateLeft ( temp->left );
            temp = rotateRight ( temp );
        }
        // Right Left Case
        else if ( balance < -1 && temp->right != NULL && key < temp->right->key ) {
            temp->right = rotateRight ( temp->right );
            temp = rotateLeft ( temp );
        }

        //return the modified root node
        return temp;
    }

    //extra function to value in the specified tree calculated using key mod s
    void insert ( const long key, long value ) {
        hashTable->node[key % s] = insert_data ( hashTable->node[key % s], key, value );
    }


    //iterator search function
    long int search_key ( avlNode* root, long int key ) {
        //cout << "Searching " << key << endl;
        while ( root != NULL ) {
            if ( root->key == key ) {
                return root->value;
            } else if ( root->key > key ) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return -1;
    }
    //search function
    long search ( long key ) {
        return search_key ( hashTable->node[ ( int ) key % s], key );
    }
    //sunction to print inorder traversal
    int inorder_key ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        //cout << "going left" << endl;
        inorder_key ( root->left );
        //cout << "printing" << endl;
        cout << root->key << " ";
        //cout << "going right" << endl;
        inorder_key ( root->right );
        return 0;
    }
    //inorder traversal
    void inorder() {
        inorder_key ( hashTable->node[1] );
    }
    //sunction to print preorder traversal
    int preorder_key ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        //cout << "else" << endl;
        cout << root->key << " ";
        preorder_key ( root->left );
        preorder_key ( root->right );
        return 0;
    }
    //preorder traversal
    void preorder() {
        preorder_key ( hashTable->node[1] );
    }
    //making root null for using the root for next iteration
    void make_root_null() {
        for ( int i = 0; i < s; i++ ) {
            hashTable->node[i] = NULL;
        }
    }




};

//util class which hold all the utility functions
class utility
{
public:
    long n;
    avlTree* tree;
    long* data;

    utility ( long n, int s ) {
        this->n = n;
        data = new long[n];
        tree = new avlTree ( s );
    }
    //function to generate shuffled array of 1000000 elements
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

        //doing shuffling
        while ( i < n / 2 ) {
            r = rand() % n;
            //cout << r << "->" << i << endl;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }
    //inserting all values in avltree
    void insert_random() {
        long i = 0;
        while ( i < n ) {
            //cout << "Inserting = " << data[i] <<  endl;
            tree->insert ( data[i], 2 * data[i] );
            i++;
        }
    }
    //searching all values present in the avltree
    void search_random() {
        long int i = 0;
        long ret;
        while ( i < n ) {
            //cout << "Searching " << data[i] << endl;
            ret = tree->search ( data[i] );
            i++;
        }
        //
    }
    //making root null to use in next iteration
    void make_root_null() {
        tree->make_root_null();
    }
    //function to calculate average of an array
    long avg ( long array[] ) {
        long sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }
    //driver function to run the AVL hash insertion and seaching 10 times and calculate avg. insert and search time.
    void random_runner() {
        clock_t start, end;
        long insert_array[10], search_array[10];
       // cout << "Experiment Running....." << endl;
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

//main function
int main()
{
    long n = 1000000;
    int s = 101;
    AVLhash::utility* util = new AVLhash::utility ( n, s );
    util->random_runner();
    return 0;
}

