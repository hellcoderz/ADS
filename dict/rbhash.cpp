#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>
#include <map>

using namespace std;

namespace RBhash
{

#define PAIR(x,y) pair<long, long>(x,y)
#define MAP map<long,long>

///utility class to hold all functions performed on rb hash tree
class utility
{
public:
    MAP* hashTable; ///hashtable variable
    int s;
    long n;
    long* data;

    utility ( int n, int s ) {
        this->s = s;
        this->n = n;
        data = new long[n];
        hashTable = new MAP[s];
    }
    ///function to generate shuffled values from 1 to n
    void generate_random() {
        ///cout << n << endl;
        long r, temp;
        long i = 0;
        data = new long[n];
        srand ( time ( 0 ) );
        while ( i < n ) {
            data[i] = i + 1;
            i++;
        }
        i = 0;
        ///loop to shuffle the array
        while ( i < n / 2 ) {
            r = rand() % n;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }

    ///function to insert shuffled values one by one into the Map
    void insert_random() {
        long i = 0;
        while ( i < n ) {
            hashTable[data[i] % s].insert ( PAIR ( data[i], 2 * data[i] ) );
            i++;
        }
    }
    ///function to search all values of the array in rb hash tree
    void search_random() {
        long int i = 0;
        long ret;
        while ( i < n ) {
            ret = hashTable[data[i] % s].find ( data[i] )->second;
            i++;
        }
        ///
    }

    ///making hashtable null to be used for next iteration
    void make_root_null() {
        for ( int i = 0; i < s; i++ ) {
            hashTable[i].clear();
        }
    }

    ///function to calculate average of an array
    double avg ( double array[] ) {
        double sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }

    ///driver function to generate, insert and search rb hash tree
    void random_runner() {
        clock_t start, end;
        double insert_array[10], search_array[10];
        for ( int i = 0; i < 10; i++ ) {
            generate_random();
            start = ((double)clock()*1000)/CLOCKS_PER_SEC;
            insert_random();
            end = ((double)clock()*1000)/CLOCKS_PER_SEC;
            insert_array[i] = end - start;
            start = ((double)clock()*1000)/CLOCKS_PER_SEC;
            search_random();
            end = ((double)clock()*1000)/CLOCKS_PER_SEC;
            search_array[i] = end - start;
            make_root_null();
        }
        cout << avg ( insert_array ) << " " <<  avg ( search_array ) << endl;    
    }

   

};

}

///driver main function
int main(int argc,char *argv[])
{
    if(argc == 4){
        //cout << argv[1] << " " << argv[2] << " " << argv[3] << endl;
        if(string(argv[1]) == "-r"){
            RBhash::utility* util = new RBhash::utility (1000000,atoi(argv[2]));
            util->random_runner();

        }else{
            cout << "wrong option" << endl;
            return 0;
        }
    }else if(argc == 3){
        if(string(argv[1]) == "-u"){
            return 0;

        }else{
            cout << "wrong option" << endl;
            return 0;
        }

    }else{
        cout << "wrong # of arguments" << endl;
        return 0;
    }
    return 0;
}
