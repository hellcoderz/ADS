#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void read_log(){
	ifstream file;
	int insert,search;
	string names[] = {"AVL tree","AVL hash","B+ tree","B+ hash","RB tree","RB hash"};
	file.open("time.log",ifstream::in);
	printf("+---------------+------------+-----------+\n");
	printf("|%14s | %10s | %10s|\n","DATA STRUCTURE","INSERT(ms)","SEARCH(ms)");
	printf("+---------------+------------+-----------+\n");
	for(int i=0;i<6;i++){
		file >> insert >> search ;
		printf("|%-14s | %10d | %10d|\n",names[i].c_str(),insert,search);
	}
	printf("+---------------+------------+-----------+\n");
	
}

int main(){
	
	int status;
	cout << "AVL tree Experiment Running ...." << endl;
	status = system("avltree >> time.log");
	cout << "AVL hash tree Experiment Running ...." << endl;
	status = system("avlhash >> time.log");
	cout << "B+ tree Experiment Running ...." << endl;
	status = system("btree >> time.log");
	cout << "B+ tree hash Experiment Running ...." << endl;
	status = system("btreehash >> time.log");
	cout << "RedBlack tree Experiment Running ...." << endl;
	status = system("rbtree >> time.log");
	cout << "RedBlack hash Experiment Running ...." << endl;
	status = system("rbhash >> time.log");
	cout << endl << "=======<Performance Analysis Table>=======" << endl;
	read_log();
	

	return 0;
}