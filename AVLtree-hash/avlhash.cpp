#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>



#define CHECK_BALANCE
#define PAIR(x,y) pair<long,node*>(x,y)

using namespace std;

class node{
public:
	long key;
	long value;
	node *left;
	node *right;
	int height;
};

typedef struct node avlNode;

class avlTree{
public:
	struct hash{
		avlNode **node;
	};


	int s;
	struct hash *hashTable; 

	avlTree(int s){
		this->s = s;
		hashTable = new hash;
		hashTable->node = new node *[s];
		for(int i=0;i<s;i++){
			hashTable->node[i] = NULL;
		}
	}


	int abs(int n){
		if(n < 0)
			return -n;
		else
			return n;
	}

	int max(int a, int b){
		if(a > b)
			return a;
		else
			return b;
	}

	int height(avlNode *root){
		if(root == NULL)
				return 0;
		return root->height;

	}

	avlNode *rotateRight(avlNode *root){
		//cout << "Rotate Right" << endl;
		avlNode *temp = root->left;
     	root->left = NULL;
		if(temp->right != NULL){
 			root->left = temp->right;
 		}
 
    	// Perform rotation
    	temp->right = root;
    	
 
   		 // Update heights
    	root->height = max(height(root->left), height(root->right))+1;
    	temp->height = max(height(temp->left), height(temp->right))+1;
 
    	// Return new root
    	return temp;

	}

	avlNode *rotateLeft(avlNode *root){
		//cout << "Rotate Left: " << root->key << endl;
		avlNode *temp = root->right;
		root->right = NULL;
		//cout << "temp->key = " << root->key << endl;
		if(temp->left != NULL){
 			root->right = temp->left;
 		}
    	// Perform rotation
    	temp->left = root;
    	
 
    	// Update heights
    	root->height = max(height(root->left), height(root->right))+1;
    	temp->height = max(height(temp->left), height(temp->right))+1;
 
    	// Return new root
    	return temp;

	}

	avlNode *insert_data(avlNode *node,long int key, long int value){
		avlNode *temp;
		if(node == NULL){
			//cout << "Insert: " << key << endl;
			node = new avlNode;
			node->left = NULL;
			node->right = NULL;
			node->key = key;
			node->value = value;
			node->height = 1;

			temp = node;
			
		}else{
			if(node->key > key){
				node->left = insert_data(node->left,key,value);
				temp = node;
				
			}else{
				node->right = insert_data(node->right,key,value);
				temp = node;				
			}
		}

		temp->height = max(height(temp->left),height(temp->right)) + 1;
		int balance = height(temp->left) - height(temp->right);

	    // If this node becomes unbalanced, then there are 4 cases
 		//cout << "Current root = " << temp->key <<  " " << "balance = " << balance << endl;
    	// Left Left Case
    	if (balance > 1 && temp->left != NULL && key < temp->left->key)
        	temp = rotateRight(temp);
 
    	// Right Right Case
    	else if (balance < -1 && temp->right != NULL && key > temp->right->key )
    	    temp = rotateLeft(temp);
 
    	// Left Right Case
    	else if (balance > 1 && temp->left != NULL && key > temp->left->key){
    	  	temp->left = rotateLeft(temp->left);
    	    temp = rotateRight(temp);
    	}
 
    	// Right Left Case
    	else if (balance < -1 && temp->right != NULL && key < temp->right->key){
    	    temp->right = rotateRight(temp->right);
    	    temp = rotateLeft(temp);
    	}
		
		return temp;
	}

	void insert(const long key, long value){
		hashTable->node[key % s] = insert_data(hashTable->node[key % s], key, value);
	}


	// search function
	long int search_key(avlNode *root,long int key){
		//cout << "Searching " << key << endl;
		while(root != NULL){
			if(root->key == key){
				return root->value;
			}else if(root->key > key){
				root = root->left;
			}else{
				root = root->right;
			}

		}
		return -1;	
	}

	long search(long key){

		return search_key(hashTable->node[(int)key % s], key);
	}

	int inorder_key(avlNode *root){

		if(root == NULL){
			return -1;
		}
		//cout << "going left" << endl;
		inorder_key(root->left);
		//cout << "printing" << endl;
		cout << root->key << " ";
		//cout << "going right" << endl;
		inorder_key(root->right);
		return 0;
	}

	void inorder(){
		inorder_key(hashTable->node[1]);
	}
	
	int preorder_key(avlNode *root){
		if(root == NULL){
			return -1;
		}
		//cout << "else" << endl;
		cout << root->key << " ";
		preorder_key(root->left);
		preorder_key(root->right);
		return 0;
	}

	void preorder(){
		preorder_key(hashTable->node[1]);
	}

	void make_root_null(){
		for(int i=0;i<s;i++){
			hashTable->node[i] = NULL;
		}
	}




};

//util class
class utility{
public:
	long n;
	avlTree *tree;
	long *data;

	utility(long n, int s){
		this->n = n;
		data = new long[n];
		tree = new avlTree(s);
	}

	 void generate_random(){
	 	//cout << n << endl;
		long r, temp;
		long i = 0;
		data = new long[n];
		srand(time(0));
		while(i < n){
			data[i] = i+1;
			i++;
		}
		i=0;

		while(i < n/2){
			
			r = rand() % n;
			//cout << r << "->" << i << endl;
			temp = data[r];
			data[r] = data[n-r-1];
			data[n-r-1] = temp;
			i++;
		}
	}

	void insert_random(){
		long i = 0;
		while(i < n){
			//cout << "Inserting = " << data[i] <<  endl;
			tree->insert(data[i],2*data[i]);
			i++;
		}
	}

	void search_random(){
		long int i = 0;
		long ret;
		while(i < n){
			//cout << "Searching " << data[i] << endl;
			ret = tree->search(data[i]);
			i++;
		}
		//
	}

	void make_root_null(){
		tree->make_root_null();
	}

	long avg(long array[]){
		long sum=0;
		for(int i=0;i<10;i++){
			sum += array[i];
		}
		return sum/10;
	}
};

//driver function
int main(){
	long n = 1000000;
	int s = 10;
	utility *util = new utility(n,s);

	clock_t start, end;
	long insert_array[10], search_array[10];
	cout << "Experiment Running....." << endl;
	for(int i=0; i<10; i++){
		
		util->generate_random();
		start = clock();
			util->insert_random();
		end = clock();
			insert_array[i] = end - start;
		start = clock();
			util->search_random();
		end = clock();
			search_array[i] = end - start;
		util->make_root_null();
		
	}
	cout << "Insert Avg. Time : " << util->avg(insert_array) << "   " << "Search Avg. Time : " << util->avg(search_array) << endl;
	
	return 0;
}

