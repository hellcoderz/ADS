#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>
#include <map>

//created data structures
#include "rbtree.h"
#include "rbhash.h"
#include "avltree.h"
#include "avlhash.h"
#include "btree.h"
#include "btreehash.h"
#include "rbtree.h"
#include "brhash.h"

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
	avlhash->random_runner();
	btree->random_runner();
	btreehash->random_runner();
	rbtree->random_runner();
	rbhash->random_runner();
	return 0;
}