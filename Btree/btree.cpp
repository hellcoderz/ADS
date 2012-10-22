<<<<<<< HEAD
#include <iostream>
#include <time.h>

using namespace std;

class node{
	public:
		long *data;
		int capacity;
		node **nodes;
		node *parent;
		node(int order){
			data = new long[order + 1];
			nodes = new node *[order + 2];
			capacity = 0;
			parent = NULL;
			for(int i=0;i<=order+1;i++){
				this->nodes[i] = NULL;
			}
		}
	
};

typedef struct node *btnode;


class btree{
	public:
		int order;

		btree(int order){
			this->order = order;
		}




		void sort_array(btnode &root){
			//btnode *root = rootx;
			long *data = &(root->data[0]);
			int last = root->capacity-1;
			long temp;
			for(int i=0;i<last;i++){
				if(root->data[last] < root->data[i]){
					temp = root->data[last];
					for(int j=last;j>i;j--){
						root->data[j] = root->data[j-1];
					}
					root->data[i] = temp;
				}
			}

			

		}

		void sort_array_with_overflow(btnode &root){
			//btnode *root = rootx; 
			long *data = &(root->data[0]);
			int last = root->capacity;
			int temp;
			for(int i=0;i<last;i++){
				if(root->data[last] < root->data[i]){
					temp = root->data[last];
					for(int j=last;j>i;j--){
						root->data[j] = root->data[j-1];
						//root->nodes[j+1] = root->nodes[j]; 
					}
					root->data[i] = temp;
				}
			}

			

		}

		void add_middle_to_parent(btnode &rootNode, btnode &parent, btnode left, btnode right, long middle){
			
			//cout << "In add middle to parent" << endl;
			//cout << "middle element = " << middle << endl;
			//cout << "Capacity = " << parent->capacity << endl;

			int i;
			for(i=0;i<parent->capacity;i++){
				if(parent->data[i] > middle)
					break;
			}
			//cout << "outside first for" << endl;
			for(int j=parent->capacity;j>i;j--){
				parent->data[j] = parent->data[j-1];
				parent->nodes[j+1] = parent->nodes[j];
			}

			//cout << "done finding index" << endl;
			parent->data[i] = middle;
			parent->nodes[i] = left;
			left->parent = parent;
			parent->nodes[i+1] = right;
			right->parent = parent;
			//cout << "done setting parent" << endl;
			if(parent->capacity <= order){
				//cout << "setting parent capacity" << endl;
				parent->capacity += 1;
				//cout << "done setting parent capacity" << endl;
				
			}else{
					split_into_children(rootNode, parent);
			}	
		}

		void split_into_children(btnode &rootNode, btnode &root){
			//btnode *root = rootx;
			//cout << "In split into  children" << endl;
			long *data = &(root->data[0]);
			//cout << "data = " << root->data[1] << endl;
			int middle = root->capacity / 2;
			int i;
			//cout << "middle element = " << root->data[middle] << endl;
			btnode left = new node(order);
			btnode right = new node(order);
			btnode temp = new node(order);
			for(int i=0;i<middle;i++){
				left->data[i] = root->data[i];
				left->capacity += 1;
				left->nodes[i] = root->nodes[i];
				//cout << "data = " << left->data[i] << endl;
				//cout << "Capacity = " << left->capacity << endl;
			}

			left->nodes[middle] = root->nodes[middle];

			for(i=0;i<root->capacity - middle;i++){
				right->data[i] = root->data[middle+1+i];
				right->capacity += 1;
				right->nodes[i] = root->nodes[middle+1+i];
				//cout << "data = " << right->data[i] << endl;
				//cout << "Capacity = " << right->capacity << endl;
			}
			right->nodes[right->capacity] = root->nodes[root->capacity + 1];
			//right->data[right->capacity] = root->data[root->capacity];
			//right->capacity += 1;

			//cout << "Right Capacity = " << right->capacity << endl;
			//cout << "Right Element = " << right->data[0] << endl;
			//cout << "rightest element = " << (root->data[root->capacity]) << endl;
				
			temp->data[0] = root->data[middle];
			temp->nodes[0] = left;
			temp->nodes[1] = right;
			temp->capacity = 1;
			
			//cout << "left data = " << temp->nodes[0]->data[0] << endl;
			//cout << "right data = " << temp->nodes[1]->data[0] << endl;

			//error - root pointer is not modified correctly
			if(root->parent == root){
				right->parent = temp;
				left->parent = temp;
				temp->parent = temp;
				rootNode = temp;
								//cout << "In root" << endl;
				//cout << "root data = " << root->data[0] << endl;
				
				
			//	cout << "Capacity = " << temp->capacity << endl;

			}else{
			
			//	cout << "parent capacity = " << root->parent->capacity << endl;
				add_middle_to_parent(rootNode, root->parent,left,right,root->data[middle]);
			}
			
		}



		void insert(btnode &rootNode, btnode &root,long data){
			//cout << "inserting " << data << endl;
			//btnode *root = rootx;
			//cout << "Order = " << order << endl;
			//cout << "parent Capacity = " << root->parent->capacity << endl;

			if(root != NULL && root->capacity < order && root->nodes[0] == NULL){
				//cout << "Capacity = " << root->capacity << endl;
				//cout << "insert in same node" << endl;
				root->data[root->capacity] = data;
				root->capacity += 1;
			//	cout << "Capacity = " << root->capacity << endl;
				sort_array(root);

			}else if(root != NULL && root->capacity == order && root->nodes[0] == NULL){
				//cout << "Capacity = " << root->capacity << endl;
				//cout << "In split" << endl;
				//cout << "parent Capacity = " << root->parent->capacity << endl;
				root->data[root->capacity] = data;
				sort_array_with_overflow(root);
				
				//cout << endl;
				split_into_children(rootNode,root);

			}else if(root != NULL){
				//cout << "insert in child node" << endl;
				//cout << "Capacity = " << root->capacity << endl;
				int i;
				for(i=0;i<root->capacity;i++){
					if(data < root->data[i])
						break;
				}
				insert(rootNode,root->nodes[i],data);

			}else if(root == NULL){
				//cout << "new node" << endl;
				root = new node(order);
				root->data[0] = data;
				root->parent = root;
				root->capacity += 1;
			}

			
		}


		int inorder(node *root){
			if(root == NULL){
				return 0;
			}
			for(int i=0;i<root->capacity;i++){
				//cout << "going left" << endl;

				inorder(root->nodes[i]);
				//cout << "printing data" << endl;
				cout << root->data[i] << " ";
				//cout << "going right" << endl;
				if(i == root->capacity - 1)
					inorder(root->nodes[i+1]);
			}
			//inorder(root->nodes[root->capacity]);
			return 0;
		}

		int preorder(btnode &root){
			//btnode *root = rootx;
			//cout << "In inorder" << endl;
			inorder:
			if(root == NULL){
				return 0;
			}
			for(int i=0;i<root->capacity;i++){
				cout << root->data[i] << " ";
				preorder(root->nodes[i]);
				if(i == root->capacity - 1)
					preorder(root->nodes[i+1]);
			}
			return 0;
		}

};

int main(){
	btnode root = NULL;
	btree tree(2);
	tree.insert(root,root,56);
	tree.insert(root,root,34);
	tree.insert(root,root,45);
	tree.insert(root,root,1);
	tree.insert(root,root,2);
	tree.insert(root,root,3);
	tree.insert(root,root,4);
	tree.insert(root,root,5);
	tree.insert(root,root,6);
	tree.insert(root,root,7);
	
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	//tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	//cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	
	//tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	//cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	
	//tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	//cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	
	//tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	//cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	/*
	cout << root->data[0] << ":" << root->capacity << " ";
	cout << root->nodes[0]->data[0] << ":" << root->nodes[0]->capacity << " ";
	cout << root->nodes[1]->data[0] << ":" << root->nodes[1]->capacity << " ";
	cout << root->nodes[0]->nodes[0]->data[0] << ":" << root->nodes[0]->nodes[0]->capacity << " ";
	cout << root->nodes[0]->nodes[1]->data[0] << ":" << root->nodes[0]->nodes[1]->capacity << " ";
	cout << root->nodes[1]->nodes[0]->data[0] << ":" << root->nodes[1]->nodes[0]->capacity << " ";
	cout << root->nodes[1]->nodes[1]->data[0] << ":" << root->nodes[1]->nodes[1]->capacity << " " << endl;
	*/
	
	
	//tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	//cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	
	//tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	//cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	
	//cout << root->nodes[1]->data[1] << endl;
	
	return 0;
=======
#include <iostream>
#include <time.h>

using namespace std;

class node{
	public:
		long *data;
		int capacity;
		node **nodes;
		node *parent;
		node(int order){
			data = new long[order + 1];
			nodes = new node *[order + 2];
			capacity = 0;
			parent = NULL;
			for(int i=0;i<=order;i++){
				this->nodes[i] = NULL;
			}
		}
	
};

typedef struct node *btnode;


class btree{
	public:
		int order;

		btree(int order){
			this->order = order;
		}




		void sort_array(btnode &root){
			//btnode *root = rootx;
			long *data = &(root->data[0]);
			int last = root->capacity-1;
			long temp;
			for(int i=0;i<last;i++){
				if(root->data[last] < root->data[i]){
					temp = root->data[last];
					for(int j=last;j>i;j--){
						root->data[j] = root->data[j-1];
					}
					root->data[i] = temp;
				}
			}

			

		}

		void sort_array_with_overflow(btnode &root){
			//btnode *root = rootx; 
			long *data = &(root->data[0]);
			int last = root->capacity;
			int temp;
			for(int i=0;i<last;i++){
				if(root->data[last] < root->data[i]){
					temp = root->data[last];
					for(int j=last;j>i;j--){
						root->data[j] = root->data[j-1];
					}
					root->data[i] = temp;
				}
			}

			

		}

		void add_middle_to_parent(btnode &parent, btnode left, btnode right, long middle){
			
			cout << "In add middle to parent" << endl;
			cout << "middle element = " << middle << endl;
			cout << "Capacity = " << parent->capacity << endl;

			int i;
			btnode rootnode;
			for(i=0;i<parent->capacity;i++){
				if(parent->data[i] > middle)
					break;
			}
			cout << "outside first for" << endl;
			for(int j=parent->capacity;j>i;j--){
				parent->data[j] = parent->data[j-1];
				parent->nodes[j+1] = parent->nodes[j];
			}

			cout << "done finding index" << endl;
			parent->data[i] = middle;
			parent->nodes[i] = left;
			left->parent = parent;
			parent->nodes[i+1] = right;
			right->parent = parent;
			cout << "done setting parent" << endl;
			if(parent->capacity < order){
				cout << "setting parent capacity" << endl;
				parent->capacity += 1;
				cout << "done setting parent capacity" << endl;
				
			}else{
					split_into_children(parent);
			}	
		}

		void split_into_children(btnode &root){
			//btnode *root = rootx;
			cout << "In split into  children" << endl;
			long *data = &(root->data[0]);
			//cout << "data = " << root->data[1] << endl;
			int middle = root->capacity / 2;
			cout << "middle element = " << root->data[middle] << endl;
			btnode left = new node(order);
			btnode right = new node(order);
			btnode temp = new node(order);
			for(int i=0;i<middle;i++){
				left->data[i] = root->data[i];
				left->capacity += 1;
				left->nodes[i] = root->nodes[i];
				cout << "data = " << left->data[i] << endl;
				cout << "Capacity = " << left->capacity << endl;
			}

			left->nodes[middle] = root->nodes[middle];

			for(int i=0;i<root->capacity - middle;i++){
				right->data[i] = root->data[middle+1+i];
				right->capacity += 1;
				right->nodes[i] = root->nodes[middle+1+i];
				cout << "data = " << right->data[i] << endl;
				cout << "Capacity = " << right->capacity << endl;
			}
			
				
			temp->data[0] = root->data[middle];
			temp->nodes[0] = left;
			temp->nodes[1] = right;
			temp->capacity = 1;
			
			//cout << "left data = " << temp->nodes[0]->data[0] << endl;
			//cout << "right data = " << temp->nodes[1]->data[0] << endl;

			//error - root pointer is not modified correctly
			if(root->parent == root){
				root = temp;
				root->parent = temp;
				cout << "In root" << endl;
				cout << "root data = " << root->data[0] << endl;
				
				right->parent = temp;
				left->parent = temp;
			//	cout << "Capacity = " << temp->capacity << endl;

			}else{
			
			//	cout << "parent capacity = " << root->parent->capacity << endl;
				add_middle_to_parent(root->parent,left,right,root->data[middle]);
			}
			
		}



		void insert(btnode &root,long data){
			//btnode *root = rootx;
			//cout << "Order = " << order << endl;
			//cout << "parent Capacity = " << root->parent->capacity << endl;

			if(root != NULL && root->capacity < order && *(root->nodes) == NULL){
				//cout << "Capacity = " << root->capacity << endl;
			//	cout << "insert in same node" << endl;
				root->data[root->capacity] = data;
				root->capacity += 1;
			//	cout << "Capacity = " << root->capacity << endl;
				sort_array(root);

			}else if(root != NULL && root->capacity == order && *(root->nodes) == NULL){
				//cout << "Capacity = " << root->capacity << endl;
				cout << "In split" << endl;
				cout << "parent Capacity = " << root->parent->capacity << endl;
				root->data[root->capacity] = data;
				sort_array_with_overflow(root);
				
				cout << endl;
				split_into_children(root);

			}else if(root != NULL){
				cout << "insert in child node" << endl;
				cout << "Capacity = " << root->capacity << endl;
				int i;
				for(i=0;i<root->capacity;i++){
					if(data < root->data[i])
						break;
				}
				insert(root->nodes[i],data);

			}else if(root == NULL){
				cout << "new node" << endl;
				root = new node(order);
				root->data[0] = data;
				root->parent = root;
				root->capacity += 1;
			}

			
		}

		int inorder(btnode &root){
			//btnode *root = rootx;
			//cout << "In inorder" << endl;
			if(root == NULL){
				return 0;
			}
			for(int i=0;i<root->capacity;i++){
				//cout << "going left" << endl;
				inorder(root->nodes[i]);
				//cout << "printing data" << endl;
				cout << root->data[i] << " ";
				//cout << "going right" << endl;
				inorder(root->nodes[i+1]);
			}
			return 0;
		}

		int preorder(btnode &root){
			//btnode *root = rootx;
			//cout << "In inorder" << endl;
			if(root == NULL){
				return 0;
			}
			for(int i=0;i<root->capacity;i++){
				cout << root->data[i] << " ";
				preorder(root->nodes[i]);
				preorder(root->nodes[i+1]);
			}
			return 0;
		}

};

int main(){
	btnode root = NULL;
	btree tree(2);
	tree.insert(root,56);
	tree.insert(root,34);
	tree.insert(root,45);
	tree.insert(root,1);
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	tree.insert(root,2);
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	tree.insert(root,3);
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	tree.insert(root,4);
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	cout << root->data[0];
	/*
	
	tree.insert(root,5);
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	tree.insert(root,6);
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	tree.insert(root,7);
	tree.inorder(root); cout << endl; tree.preorder(root); cout << endl;
	cout << "++++++++++++++++++++ Capacity = " << root->capacity << endl;
	*/
	return 0;
>>>>>>> 42df1b39377ff7825b57f1a2f0c8f0bfede6e107
}