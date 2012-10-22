#include <iostream>
#include <time.h>
#include <stdio.h>

#define CHECK_BALANCE

using namespace std;

struct node{
	long key;
	node *left;
	node *right;
	int height;
	long value;
};

typedef struct node avlNode;

class avlTree{
public:
	
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



	avlNode *insert(avlNode *node,long data){
		avlNode *temp;
		if(node == NULL){
			//cout << "Insert: " << data << endl;
			node = (avlNode *)new avlNode;
			node->left = NULL;
			node->right = NULL;
			node->key = data;
			node->height = 0;
			
		}else{
			if(node->key > data){
				node->left = insert(node->left,data);
				temp = node;
				temp->height = height(temp->left) - height(temp->right);
				#ifdef CHECK_BALANCE
				if(temp->height == -2 || temp->height == 2){
					//cout << "left balancing" << endl;
					if(temp->key < data && temp->right->key > data)
						node = rotateRightTwice(temp);
					else if(temp->key < data && temp->right->key < data)
						node = rotateRightOnce(temp);
					else if(temp->key > data && temp->left->key < data)
						node = rotateLeftTwice(temp);
					else if(temp->key > data && temp->left->key > data)
						node = rotateLeftOnce(temp);
				}
				#endif
			}else{
				node->right = insert(node->right,data);
				temp = node;
				temp->height = height(temp->left) - height(temp->right);
				#ifdef CHECK_BALANCE
				if(temp->height == -2 || temp->height == 2){
					//cout << "right balancing" << endl;
					if(temp->key < data && temp->right->key > data)
						node = rotateRightTwice(temp);
					else if(temp->key < data && temp->right->key < data)
						node = rotateRightOnce(temp);
					else if(temp->key > data && temp->left->key < data)
						node = rotateLeftTwice(temp);
					else if(temp->key > data && temp->left->key > data)
						node = rotateLeftOnce(temp);
				}
				#endif
			}
		}
		
		return node;
	}




	// search function
	bool search(avlNode *root,long data){
		avlNode *temp = root;
		
		if(temp->key == data){
			return 1;
		}else{
			if(temp->key > data){
				if(temp->left == NULL)
					return 0;
				else
					return search(temp->left,data);
			}else{
				if(temp->right == NULL)
					return 0;
				else
					return search(temp->right,data);
			}
		}

		
	}

	int inorder(avlNode *root){
		if(root == NULL){
			return -1;

		}

		//cout << "else" << endl;
		inorder(root->left);
		cout << root->key << ":" << root->height << " ";
		inorder(root->right);
		
		return 0;
	}
};

//driver function
int main(){
	avlTree tree;
	node *root = NULL;
	root = tree.insert(root,4);

	root = tree.insert(root,6);
	root = tree.insert(root,9);
	root = tree.insert(root,5);
	

	//cout << root->key << endl;
	
	//search
	cout << tree.search(root,5) << endl;
	tree.inorder(root);
	//cout << endl << "tree height = " << root->height(root)  << endl;
	//cout << "left subtree height = " << root->height(root->left)  << endl;
	//cout << "right subtree height = " << root->height(root->right)  << endl;
	return 0;
}

