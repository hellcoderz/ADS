#include <iostream>
#include <time.h>
#include <stdio.h>
#include <map>
#include <ctime>
#include <cstdlib>


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

	avlNode *rotateLeftOnce(avlNode *node){
	 //cout << "rotateLeftOnce" << endl;
     avlNode *otherNode;

     otherNode = node->left;
     node->left = otherNode->right;
     otherNode->right = node;
     node = otherNode;

     node->height = 0;
     node->right->height = 0;
     return node;
	}

	avlNode *rotateRightOnce(avlNode *node){
	 //cout << "rotateRightOnce" << endl;
     avlNode *otherNode;

     otherNode = node->right;
     node->right = otherNode->left;
     otherNode->left = node;
     node = otherNode;

     node->height = 0;
     node->left->height = 0;
     return node;
	}

	avlNode *rotateLeftTwice(avlNode *node){
	 avlNode *temp = node->left;
	 //cout << "rotateLeftTwice" << endl;
     avlNode *otherNode = temp;

     otherNode = temp->right;
     temp->right = otherNode->left;
     otherNode->left = temp;
     temp = otherNode;

     temp->height = 0;
     temp->left->height = 0;
     node->left = temp;
     return rotateLeftOnce(node);
	}

	avlNode *rotateRightTwice(avlNode *node){
	 avlNode *temp = node->right;
	 //cout << "rotateRightTwice" << endl;
     avlNode *otherNode;

     otherNode = temp->left;
     temp->left = otherNode->right;
     otherNode->right = temp;
     temp = otherNode;

     temp->height = 0;
     temp->right->height = 0;
     node->right = temp;
     return rotateRightOnce(node);
	}

	int height(avlNode *root){
		if(root == NULL)
				return -1;

		int lh = height(root->left);
		int rh = height(root->right);
		if(lh > rh)
			return 1 + lh;
		else
			return 1 + rh;

	}



	avlNode *insert_data(avlNode *node, const long key, long data){
		avlNode *temp;
		if(node == NULL){
			//cout << "Insert: " << data << endl;
			node = (avlNode *)new avlNode;
			node->left = NULL;
			node->right = NULL;
			node->key = key;
			node->value = data;
			node->height = 0;
			
		}else{
			if(node->key > key){
				node->left = insert_data(node->left, key, data);
				temp = node;
				temp->height = height(temp->left) - height(temp->right);
				#ifdef CHECK_BALANCE
				if(temp->height == -2 || temp->height == 2){
					//cout << "left balancing" << endl;
					if(temp->key < key && temp->right->key > key)
						node = rotateRightTwice(temp);
					else if(temp->key < key && temp->right->key < key)
						node = rotateRightOnce(temp);
					else if(temp->key > key && temp->left->key < key)
						node = rotateLeftTwice(temp);
					else if(temp->key > key && temp->left->key > key)
						node = rotateLeftOnce(temp);
				}
				#endif
			}else{
				node->right = insert_data(node->right, key, data);
				temp = node;
				temp->height = height(temp->left) - height(temp->right);
				#ifdef CHECK_BALANCE
				if(temp->height == -2 || temp->height == 2){
					//cout << "right balancing" << endl;
					if(temp->key < key && temp->right->key > key)
						node = rotateRightTwice(temp);
					else if(temp->key < key && temp->right->key < key)
						node = rotateRightOnce(temp);
					else if(temp->key > key && temp->left->key < key)
						node = rotateLeftTwice(temp);
					else if(temp->key > key && temp->left->key > key)
						node = rotateLeftOnce(temp);
				}
				#endif
			}
		}
		
		return node;
	}

	void insert(const long key, long value){
		hashTable->node[key % s] = insert_data(hashTable->node[key % s], key, value);
	}


	// search function
	long search_key(avlNode *root,long key){
		avlNode *temp = root;
		//cout << "search term = " << temp->key << endl;
		if(temp == NULL)
			return -1;
		if(temp->key == key){
			return temp->value;
		}else{
			if(temp->key > key){
				if(temp->left == NULL)
					return -1;
				else
					return search_key(temp->left,key);
			}else{
				if(temp->right == NULL)
					return -1;
				else
					return search_key(temp->right,key);
			}
		}
	
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
		n = 100;
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

	long search(long key){
		return tree->search(key);
	}
};

//driver function
int main(){
	long n = 100;
	int s = 3;
	avlNode *root = NULL;
	utility *util = new utility(n,s);
	util->generate_random();
	util->insert_random();
	cout << util->search(56);
	
	return 0;
}

