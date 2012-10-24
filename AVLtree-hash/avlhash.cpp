#include <iostream>
#include <time.h>
#include <stdio.h>
#include <map>

#define CHECK_BALANCE
#define PAIR(x,y) pair<long,node*>(x,y)

using namespace std;

struct Comparer {
    bool operator() (const long &b1, const long &b2) const {
        return b1.to_long() < b2.to_long();
    }
};

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
	map<long,node*,Comparer> *table;
	pair<const long,node*> *hashmap;
	int s;

	avlTree(int s){
		this->s = s;
		
		for(int i=0;i<s;i++){
			table->insert(PAIR((long)i,new avlNode));
			table->find(i)->second = NULL;
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
			if(node->key > data){
				node->left = insert_data(node->left, key, data);
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
				node->right = insert_data(node->right, key, data);
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

	void insert(const long key, long value){
		table->find(key%s)->second = insert_data(table->find(key%s)->second, key, value);
	}


	// search function
	long search_key(avlNode *root,long key){
		avlNode *temp = root;
		
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

		return search_key(table->find(key%s)->second,key);
	}

	int inorder(avlNode *root){
		if(root == NULL){
			return -1;
		}
		//cout << "else" << endl;
		inorder(root->left);
		cout << root->key << " ";
		inorder(root->right);
		return 0;
	}
	
	int preorder(avlNode *root){
		if(root == NULL){
			return -1;
		}
		//cout << "else" << endl;
		cout << root->key << " ";
		inorder(root->left);
		inorder(root->right);
		return 0;
	}


};

//driver function
int main(){
	
	int s=3;
	avlTree tree(s);

	tree.insert(56,34);
	tree.insert(34,57);
	tree.insert(45,67);
	tree.insert(1,56);
	tree.insert(2,89);
	tree.insert(3,80);
	tree.insert(4,23);
	tree.insert(5,12);
	tree.insert(6,234);
	tree.insert(7,456);
	

	//cout << root->key << endl;
	
	//search
	cout << tree.search(5) << endl;
	//tree.inorder(root);	cout << endl; tree.preorder(root); cout << endl;

	//cout << endl << "tree height = " << root->height(root)  << endl;
	//cout << "left subtree height = " << root->height(root->left)  << endl;
	//cout << "right subtree height = " << root->height(root->right)  << endl;
	return 0;
}

