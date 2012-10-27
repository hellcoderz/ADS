#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>


namespace AVLtree
{

#define CHECK_BALANCE

using namespace std;


struct node {

    long int key;
    node* left;
    node* right;
    int height;
    long int value;

};



typedef struct node avlNode;



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
    avlNode* insert( avlNode* node, long int key, long int value ) {
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
                node->left = insert ( node->left, key, value );
                temp = node;

                //condition to check if key should be added in the right subtree
            } else {
                node->right = insert ( node->right, key, value );
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









    // search function

    long int search ( avlNode* root, long int key ) {
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


    //function to print inorder traversal
    int inorder ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        //cout << "else" << endl;
        inorder ( root->left );
        int balance = height ( root->left ) - height ( root->right );
        cout << root->key << ":" << balance << " ";
        inorder ( root->right );
        return 0;
    }


    //function to print preorder traversal
    int preorder ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        //cout << "else" << endl;
        cout << root->key << " ";
        preorder ( root->left );
        preorder ( root->right );
        return 0;
    }


    //function to print level order traversal using queues
    int level_order ( avlNode* root ) {
        //cout << "LEVEL OREDER TRAVERSAL STARTED" << endl;
        //cout << endl;
        queue<avlNode*> que;    //creating queue to hold all children 
        avlNode* temp;
        que.push ( root );
        while ( !que.empty() ) {
            temp = que.front();
            que.pop();
            if ( root == NULL )
                return 0;
            cout << temp->key  << " ";
            que.push ( temp->left );
            que.push ( temp->right );
            //cout << endl;
        }
        cout << endl;
        //cout << "LEVEL OREDER TRAVERSAL ENDED" << endl;
        return 0;
    }



};


//utility class to hold all functions used to generate and insert random and user define key values
class utility
{

public:

    long int n;
    avlNode* root;
    avlTree tree;
    long int* data;
    //constructor
    utility ( const long int n ) {
        //cout << n << endl;
        this->n = n;
        root = NULL;
        data = new long[n];
    }
    //function to generate shuffled values from 1 to n
    void generate_random() {
        //cout << n << endl;
        long int r, temp;
        long int i = 0;
        data = new long int[n];
        srand ( time ( 0 ) );
        while ( i < n ) {
            data[i] = i + 1;
            //cout << data[i] << " ";
            i++;
        }
        //cout << endl;
        i = 0;
        //shuffing the array
        while ( i < n / 2 ) {
            r = rand() % n;
            //cout << r << "->" << i << endl;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }
    //function to generate values in decreasing order
    void generate_decreasing() {
        long int i = n;
        while ( i > 0 ) {
            data[n - i] = i;
            //cout << data[n-i] << " ";
            i--;
        }
        //cout << endl;
    }
    //function to generate values in increasing order
    void generate_increasing() {
        long int i = 0;
        while ( i < n ) {
            data[i] = i + 1;
            //cout << data[n-i] << " ";
            i++;
        }
        //cout << endl;
    }


    //function to insert random values in avltree
    void insert_random() {
        //cout << "Insert Started" << endl;
        long int i = 0;
        while ( i < n ) {
            //cout << "Inserting = " << data[i] <<  endl;
            root = tree.insert ( root, data[i], 2 * data[i] );
            //cout << "tree height = " << tree.height(root) <<  endl;
            i++;
        }
        //cout << data[4] << endl;
    }


    //function to insert predefined values for testing
    void insert_defined() {
        int d[] = {20, 19, 18, 4, 16, 6, 7, 13, 9, 11, 10, 12, 8, 14};
        for ( int i = 0; i < sizeof ( d ) / sizeof ( int ); i++ ) {
            cout << "Inserting = " << d[i] <<  endl;
            root = tree.insert ( root, d[i], 2 * d[i] );
            inorder_random();
            preorder_random();
            //tree.level_order(root);
        }
    }


    //searching all values in shuffled order in avl tree
    void search_random() {
        //cout << "Search Started" << endl;
        long int i = 0;
        long ret;
        while ( i < n ) {
            //cout << "Searching " << data[i] << endl;
            ret = tree.search ( root, data[i] );
            i++;
        }
        //cout << endl;
    }
    //printing inordertraversal
    void inorder_random() {
        //cout << "generating inorder traversal" << endl;
        tree.inorder ( root );
        //cout << endl << "inorder traversal ended" << endl;
    }
    //printing preorder traversal
    void preorder_random() {
       // cout << "generating preorder traversal" << endl;
        tree.preorder ( root );
        //cout << endl << "preorder traversal ended" << endl;
    }
    //making root null
    void make_root_null() {
        root = NULL;
    }
    //print root height
    void height() {
        cout << "tree height = " << tree.height ( root ) << endl;
    }
    //function to calculate average of the array
    long avg ( long array[] ) {
        long sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }
    //function to run the experiment including generating, inserting and searching;
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
        cout  << avg ( insert_array ) << " " <<  avg ( search_array ) << endl;    
    }

};



}



//driver function

int main()
{
    long int n;
    AVLtree::utility* util = new AVLtree::utility ( 1000000 );
    util->random_runner();
    return 0;
}



