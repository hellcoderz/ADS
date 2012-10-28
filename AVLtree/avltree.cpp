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



class avlTree
{

public:

    int abs ( int n ) {
        if ( n < 0 )
            return -n;
        else
            return n;
    }



    int max ( int a, int b ) {
        if ( a > b )
            return a;
        else
            return b;
    }



    int height ( avlNode* root ) {
        if ( root == NULL )
            return 0;
        return root->height;
    }



    avlNode* rotateRight ( avlNode* root ) {
        //cout << "Rotate Right" << endl;
        avlNode *temp = root->left;
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



    avlNode* rotateLeft ( avlNode* root ) {
        //cout << "Rotate Left: " << root->key << endl;
        avlNode *temp = root->right;
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



    avlNode* insert ( avlNode* node, long int key, long int value ) {
       
        if ( node == NULL ) {
            //cout << "Insert: " << key << endl;
            node = new avlNode;
            node->left = NULL;
            node->right = NULL;
            node->key = key;
            node->value = value;
            node->height = 1;
            
        } else {
            if ( node->key > key ) {
                node->left = insert ( node->left, key, value );
                
            } else {
                node->right = insert ( node->right, key, value );
                
            }
        }
        node->height = max ( height ( node->left ), height ( node->right ) ) + 1;
        int balance = height ( node->left ) - height ( node->right );
        // If this node becomes unbalanced, then there are 4 cases
        //cout << "Current root = " << node->key <<  " " << "balance = " << balance << endl;
        // Left Left Case
        if ( balance > 1 && node->left != NULL && key < node->left->key )
            node = rotateRight ( node );
        // Right Right Case
        else if ( balance < -1 && node->right != NULL && key > node->right->key )
            node = rotateLeft ( node );
        // Left Right Case
        else if ( balance > 1 && node->left != NULL && key > node->left->key ) {
            node->left = rotateLeft ( node->left );
            node = rotateRight ( node );
        }
        // Right Left Case
        else if ( balance < -1 && node->right != NULL && key < node->right->key ) {
            node->right = rotateRight ( node->right );
            node = rotateLeft ( node );
        }
        return node;
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



    int level_order ( avlNode* root ) {
        cout << "LEVEL OREDER TRAVERSAL STARTED" << endl;
        //cout << endl;
        queue<avlNode*> que;
        avlNode* temp;
        que.push ( root );
        while ( !que.empty() ) {
            temp = que.front();
            que.pop();
            if ( root == NULL )
                return 0;
            cout << temp->key  << ":" << temp->height << " ";
            que.push ( temp->left );
            que.push ( temp->right );
            //cout << endl;
        }
        cout << "LEVEL OREDER TRAVERSAL ENDED" << endl;
        return 0;
    }



};



class utility
{

public:

    long int n;

    avlNode* root;

    avlTree tree;

    long int* data;



    utility ( const long int n ) {
        //cout << n << endl;
        this->n = n;
        root = NULL;
        data = ( long int* ) malloc ( sizeof ( long ) * n );
    }



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
        while ( i < n / 2 ) {
            r = rand() % n;
            //cout << r << "->" << i << endl;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }

    void generate_decreasing() {
        long int i = n;
        while ( i > 0 ) {
            data[n - i] = i;
            //cout << data[n-i] << " ";
            i--;
        }
        //cout << endl;
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

    void inorder_random() {
        cout << "generating inorder traversal" << endl;
        tree.inorder ( root );
        cout << endl << "inorder traversal ended" << endl;
    }

    void preorder_random() {
        cout << "generating preorder traversal" << endl;
        tree.preorder ( root );
        cout << endl << "preorder traversal ended" << endl;
    }



    void make_root_null() {
        root = NULL;
    }



    void height() {
        cout << "tree height = " << tree.height ( root ) << endl;
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
        cout << "Experiment Running....." << endl;
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
        cout << "Insert Avg. Time : " << avg ( insert_array ) << "   " << "Search Avg. Time : " << avg ( search_array ) << endl;
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



