#include <iostream>

using namespace std;

struct x{
	int data;
	struct x *ptr;
};

typedef struct x *node;
class test{
public:
	node n;

	test(){
		n=NULL;
	}

	node add(node &root, int data){
		root->ptr = new x();
		root->ptr->data = data;
		
		return root;
	}
};

int main(){
	node root = NULL;

	test t;
	root = t.add(root,5);
	root = t.add(root,6);

	//cout << (root->ptr)->data << endl << (root->ptr->ptr)->data << endl;
}