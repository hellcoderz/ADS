#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>
#include <fstream>
using namespace std;


namespace AVLhash
{

#define CHECK_BALANCE
#define PAIR(x,y) pair<long,node*>(x,y)


/// node structure of avltree
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
    /// hashmap to store s no. of of trees
    struct hash {
        avlNode** node;
    };


    int s;
    struct hash* hashTable;
    FILE *file_in;
    /// constructor
    avlTree ( int s ) {
        this->s = s;
        file_in = fopen("AVLHash_inorder.out","wt");
        hashTable = new hash; /// allocating space for hash table
        hashTable->node = new node *[s]; /// allocating space for s avl trees
        for ( int i = 0; i < s; i++ ) {
            hashTable->node[i] = NULL;  /// making all roots NULL of each avltree
        }
    }

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
    avlNode* insert_data ( avlNode* node, long int key, long int value ) {
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
                node->left = insert_data ( node->left, key, value );
                temp = node;

                ///condition to check if key should be added in the right subtree
            } else {
                node->right = insert_data ( node->right, key, value );
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

    ///extra function to value in the specified tree calculated using key mod s
    void insert (  long key, long value ) {
        hashTable->node[key % s] = insert_data ( hashTable->node[key % s], key, value );
    }


    ///iterator search function
    long int search_key ( avlNode* root, long int key ) {
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
    ///search function
    long search ( long key ) {
        return search_key ( hashTable->node[ ( int ) key % s], key );
    }
    ///sunction to print inorder traversal
    int inorder_key ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        inorder_key ( root->left );
        cout << root->key << " ";
        inorder_key ( root->right );
        return 0;
    }
    ///inorder traversal
    void inorder() {
        inorder_key ( hashTable->node[1] );
    }

    ///inorder traversal and storin in file
    int inorder_file ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        inorder_file ( root->left );
        fprintf(file_in,"%ld ",root->value);
        inorder_file ( root->right );
        return 0;
    }
    ///abstract function to call inorder for each hash node
    void inorder_file_hash(){
        for(int i=0;i<s;i++){
            inorder_file(hashTable->node[i]);   //selecting root corresponding to key mod s
            fprintf(file_in, "\n");
        }
    }

    ///sunction to print preorder traversal
    int preorder_key ( avlNode* root ) {
        if ( root == NULL ) {
            return -1;
        }
        cout << root->value << " ";
        preorder_key ( root->left );
        preorder_key ( root->right );
        return 0;
    }
    ///preorder traversal
    void preorder() {
        preorder_key ( hashTable->node[1] );
    }
    ///making root null for using the root for next iteration
    void make_root_null() {
        for ( int i = 0; i < s; i++ ) {
            hashTable->node[i] = NULL;
        }
    }




};

///util class which hold all the utility functions
class utility
{
public:
    long n;
    avlTree* tree;
    long* data;
    

    utility ( ) {
       
        
        
    }
    ///function to generate shuffled array of 1000000 elements
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

        ///doing shuffling
        while ( i < n / 2 ) {
            r = rand() % n;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }
    ///inserting all values in avltree
    void insert_random() {
        long i = 0;
        while ( i < n ) {
           
            tree->insert ( data[i], 2 * data[i] );
            i++;
        }
    }
    ///searching all values present in the avltree
    void search_random() {
        long int i = 0;
        long ret;
        while ( i < n ) {
            ret = tree->search ( data[i] );
            i++;
        }
        ///
    }
    ///making root null to use in next iteration
    void make_root_null() {
        tree->make_root_null();
    }
    ///function to calculate average of an array
    double avg ( double array[] ) {
        double sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }
    ///driver function to run the AVL hash insertion and seaching 10 times and calculate avg. insert and search time.
    void random_runner(long num, int s) {
        n = num;
        data = new long[n];
        tree = new avlTree ( s );
        clock_t start, end;
        double insert_array[10], search_array[10];
        for ( int i = 0; i < 10; i++ ) {
            generate_random();
            start = ((double)clock()*1000)/CLOCKS_PER_SEC;
            insert_random();
            end = ((double)clock()*1000)/CLOCKS_PER_SEC;
            insert_array[i] = end - start;
            start = ((double)clock()*1000)/CLOCKS_PER_SEC;
            search_random();
            end = ((double)clock()*1000)/CLOCKS_PER_SEC;
            search_array[i] = end - start;
            make_root_null();
        }
        cout << avg ( insert_array ) << " " <<  avg ( search_array ) << endl;
    }

    


    ///function to input data from user and output traversal in file
    void user_runner(char file[], int s){
        ifstream infile;    /// create file for input
        tree = new avlTree ( s );
        infile.open(file,ifstream::in);
        infile >> n;
        long i=0;
        long key, value;
        while(i<n){     ///loop to insert values from file
            infile >> key >> value ;
            
            tree->insert (key, value );
            i++;
        }

        tree->inorder_file_hash();  ///inorder traversal and output is stored in file
       

    }
};

}

///main function
int main(int argc,char *argv[])
{
    
    AVLhash::utility* util = new AVLhash::utility ();
    if(argc == 4){  //checking for valid # of arguments
        //cout << argv[1] << " " << argv[2] << " " << argv[3] << endl;
        if(string(argv[1]) == "-r"){    //random mode
            //cout << "random mode" << endl;
            //printf("%d\n",atoi(argv[2]));
            util->random_runner(1000000,atoi(argv[2]));

        }else{
            cout << "wrong option" << endl;
            return 0;
        }
    }else if(argc == 3){
        if(string(argv[1]) == "-u"){    //user mode
            //cout << "user mode" << endl;
            util->user_runner(argv[2],3);
           // util->inorder();

        }else{
            cout << "wrong option" << endl;
            return 0;
        }

    }else{
        cout << "wrong # of arguments" << endl;
        return 0;
    }
    return 0;
}

