#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
///function to read 'time.log' file and generate a table.
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
///driver function to run all data structures and store their insertion and searching time in 'time.log' file.
int main(int argc,char *argv[])
{	
	int status;
	string str;

	if(argc == 4){	/// check for random mode
        
        if(string(argv[1]) == "-r"){
            str = string("-r ") + string(argv[2]) + string(" ") + string(argv[3]) + string(" >> time.log");
            cout << "AVL tree Experiment Running ...." << endl;
			status = system(string(string("./avltree ") + str).c_str());
			cout << "AVL hash tree Experiment Running ...." << endl;
			status = system(string(string("./avlhash ") + str).c_str());
			cout << "B+ tree Experiment Running ...." << endl;
			status = system(string(string("./btree ") + str).c_str());
			cout << "B+ tree hash Experiment Running ...." << endl;
			status = system(string(string("./btreehash ") + str).c_str());
			cout << "RedBlack tree Experiment Running ...." << endl;
			status = system(string(string("./rbtree ") + str).c_str());
			cout << "RedBlack hash Experiment Running ...." << endl;
			status = system(string(string("./rbhash ") + str).c_str());
			cout << endl << "=======<Performance Analysis Table>=======" << endl;
			read_log();

        }else{
            cout << "wrong option" << endl;
            return 0;
        }
    }else if(argc == 3){	//check for user mode
        if(string(argv[1]) == "-u"){
           str = string("-u ") + string(argv[2]) + string(" >> time.log");
           cout << "Writing AVL_inorder.out and AVL_postorder.out ...." << endl;
			status = system(string(string("avltree ") + str).c_str());
			cout << "Writing AVLHash_inorder.out ...." << endl;
			status = system(string(string("avlhash ") + str).c_str());
			cout << "Writing BTree_level.out and BTree_sorted.out ...." << endl;
			status = system(string(string("btree ") + str).c_str());
			cout << "Writing BTreeHash_level.out ...." << endl;
			status = system(string(string("btreehash ") + str).c_str());

        }else{
            cout << "wrong option" << endl;
            return 0;
        }

    }else{
        cout << "wrong # of arguments" << endl;
        return 0;
    }

    status = system("rm time.log");
	
	

	return 0;
}
