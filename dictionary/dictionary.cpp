#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>
#include <map>

//created data structures
#include "rbhash.h"
#include "avltree.h"
#include "avlhash.h"
#include "btree.h"
#include "btreehash.h"
#include "rbtree.h"

using namespace std;

int main(){
	long n = 1000000;
	int s = 11;
	int order = 50;

	AVLtree::utility *avltree = new AVLtree::utility(n);
	AVLhash::utility *avlhash = new AVLhash::utility(n,s);
	Btree::utility *btree = new Btree::utility(n,order-1);
	Btreehash::utility *btreehash = new Btreehash::utility(n,order-1,s);
	RBtree::utility *rbtree = new RBtree::utility(n);
	RBhash::utility *rbhash = new RBhash::utility(n,s);

	avltree->random_runner();
	delete avltree;
	avlhash->random_runner();
	delete avlhash;
	rbtree->random_runner();
	delete rbtree;
	rbhash->random_runner();
	delete rbhash;
	btree->random_runner();
	delete btree;
	btreehash->random_runner();
	delete btreehash;
	
	return 0;
}