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


class node
{
public:
    long key;   ///node key
    long value; ///node value
    node* left; ///left child
    node* right;    ///right child
    int height; ///height of the tree i.e. max height from left or right subtree
};

typedef struct node avlNode;    ///just an alias

/// avlhash tree class containing all functions of the tree
class avlTree
{
public:

    ///absoulute value function
    int abs ( int n ) {
        if ( n < 0 )
            return -n;
        else
            return n;
    }
    /// function to find max of the two numbers
    int max ( int a, int b ) {
        if ( a > b )
            return a;
        else
            return b;
    }
    ///function to the height of that node in the avltree
    int height ( avlNode* root ) {
        if ( root == NULL )
            return 0;
        return root->height;
    }
    /// function to perform right rotation
    avlNode* rotateRight ( avlNode* root ) {
        avlNode* temp = root->left;
        root->left = NULL;
        if ( temp->right != NULL ) {
            root->left = temp->right;
        }
        /// Perform rotation
        temp->right = root;
        /// Update heights
        root->height = max ( height ( root->left ), height ( root->right ) ) + 1;
        temp->height = max ( height ( temp->left ), height ( temp->right ) ) + 1;
        /// Return new root
        return temp;
    }
    ///function to perform left rotation
    avlNode* rotateLeft ( avlNode* root ) {
        avlNode* temp = root->right;
        root->right = NULL;
        if ( temp->left != NULL ) {
            root->right = temp->left;
        }
        /// Perform rotation
        temp->left = root;
        /// Update heights
        root->height = max ( height ( root->left ), height ( root->right ) ) + 1;
        temp->height = max ( height ( temp->left ), height ( temp->right ) ) + 1;
        /// Return new root
        return temp;
    }



 /// function to insert key and values in the avl tree
    avlNode* insert( avlNode* node, long int key, long int value ) {
        avlNode* temp;

        ///condition when tree is subtree is empty and new node can be inserted here
        if ( node == NULL ) {
            node = new avlNode;
            node->left = NULL;
            node->right = NULL;
            node->key = key;
            node->value = value;
            node->height = 1;
            temp = node;

            ///condition to check if key should be added in the left subtree
        } else {
            if ( node->key > key ) {
                node->left = insert ( node->left, key, value );
                temp = node;

                ///condition to check if key should be added in the right subtree
            } else {
                node->right = insert ( node->right, key, value );
                temp = node;
            }
        }

        /// update height of the parent node
        temp->height = max ( height ( temp->left ), height ( temp->right ) ) + 1;
        ///calculate the balance height of the parent node
        int balance = height ( temp->left ) - height ( temp->right );
        /// If this node becomes unbalanced, then there are 4 cases
        /// Left Left Case
        if ( balance > 1 && temp->left != NULL && key < temp->left->key )
            temp = rotateRight ( temp );
        /// Right Right Case
        else if ( balance < -1 && temp->right != NULL && key > temp->right->key )
            temp = rotateLeft ( temp );
        /// Left Right Case
        else if ( balance > 1 && temp->left != NULL && key > temp->left->key ) {
            temp->left = rotateLeft ( temp->left );
            temp = rotateRight ( temp );
        }
        /// Right Left Case
        else if ( balance < -1 && temp->right != NULL && key < temp->right->key ) {
            temp->right = rotateRight ( temp->right );
            temp = rotateLeft ( temp );
        }

        ///return the modified root node
        return temp;
    }


    /// search function

    long int search ( avlNode* root, long int key ) {
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


    ///function to print inorder traversal
    int inorder ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        inorder ( root->left );
        int balance = height ( root->left ) - height ( root->right );
        cout << root->key << ":" << balance << " ";
        inorder ( root->right );
        return 0;
    }


    ///function to print preorder traversal
    int preorder ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        cout << root->key << " ";
        preorder ( root->left );
        preorder ( root->right );
        return 0;
    }


    ///function to print level order traversal using queues
    int level_order ( avlNode* root ) {
        queue<avlNode*> que;    ///creating queue to hold all children 
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
        }
        cout << endl;
        return 0;
    }



};


///utility class to hold all functions used to generate and insert random and user define key values
class utility
{

public:

    long int n;
    avlNode* root;
    avlTree tree;
    long int* data;
    ///constructor
    utility ( const long int n ) {
        this->n = n;
        root = NULL;
        data = new long[n];
    }
    ///function to generate shuffled values from 1 to n
    void generate_random() {
        long int r, temp;
        long int i = 0;
        data = new long int[n];
        srand ( time ( 0 ) );
        while ( i < n ) {
            data[i] = i + 1;
            i++;
        }
        i = 0;
        ///shuffing the array
        while ( i < n / 2 ) {
            r = rand() % n;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }
    ///function to generate values in decreasing order
    void generate_decreasing() {
        long int i = n;
        while ( i > 0 ) {
            data[n - i] = i;
            i--;
        }
    }
    ///function to generate values in increasing order
    void generate_increasing() {
        long int i = 0;
        while ( i < n ) {
            data[i] = i + 1;
            i++;
        }
    }


    ///function to insert shuffled values in avltree
    void insert_random() {
        long int i = 0;
        while ( i < n ) {
            root = tree.insert ( root, data[i], 2 * data[i] );
            i++;
        }
    }


    ///function to insert predefined values for testing
    void insert_defined() {
        int d[] = {20, 19, 18, 4, 16, 6, 7, 13, 9, 11, 10, 12, 8, 14};
        for ( int i = 0; i < sizeof ( d ) / sizeof ( int ); i++ ) {
            cout << "Inserting = " << d[i] <<  endl;
            root = tree.insert ( root, d[i], 2 * d[i] );
            inorder_random();
            preorder_random();
        }
    }


    ///searching all values in shuffled order in avl tree
    void search_random() {
        long int i = 0;
        long ret;
        while ( i < n ) {
            ret = tree.search ( root, data[i] );
            i++;
        }
    }
    ///printing inorder traversal
    void inorder_random() {
        ///cout << "generating inorder traversal" << endl;
        tree.inorder ( root );
        ///cout << endl << "inorder traversal ended" << endl;
    }
    ///printing preorder traversal
    void preorder_random() {
       /// cout << "generating preorder traversal" << endl;
        tree.preorder ( root );
        ///cout << endl << "preorder traversal ended" << endl;
    }
    ///making root null for next iteration
    void make_root_null() {
        root = NULL;
    }
    ///print root height
    void height() {
        cout << "tree height = " << tree.height ( root ) << endl;
    }
    ///function to calculate average of the array
    long avg ( long array[] ) {
        long sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }
    ///function to run the experiment including generating, inserting and searching;
    void random_runner() {
        clock_t start, end;
        long insert_array[10], search_array[10];
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



///driver function

int main()
{
    long int n;
    AVLtree::utility* util = new AVLtree::utility ( 1000000 );
    util->random_runner();
    return 0;
}
