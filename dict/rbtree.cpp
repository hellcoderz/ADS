#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <queue>
#include <map>

using namespace std;
namespace RBtree
{

#define PAIR(x,y) pair<long, long>(x,y)
#define MAP map<long,long>

//utility class to hold all functions performed on rb hash tree
class utility
class utility
{
public:
    MAP hashmap;
    int s;
    long n;
    long* data;

    utility ( int n ) {
        this->n = n;
        data = new long[n];
    }

    //function to generate shuffled values from 1 to n
    void generate_random() {
        //cout << n << endl;
        long r, temp;
        long i = 0;
        data = new long[n];
        srand ( time ( 0 ) );
        while ( i < n ) {
            data[i] = i + 1;
            i++;
        }
        i = 0;
        //loop to shuffle the array
        while ( i < n / 2 ) {
            r = rand() % n;
            //cout << r << "->" << i << endl;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }

    //function to insert shuffled values one by one into the Map
    void insert_random() {
        long i = 0;
        while ( i < n ) {
            //cout << "Inserting = " << data[i] <<  endl;
            hashmap.insert ( PAIR ( data[i], 2 * data[i] ) );
            i++;
        }
    }

    //function to search all values of the array in rb hash tree
    void search_random() {
        long int i = 0;
        long ret;
        while ( i < n ) {
            //cout << "Searching " << data[i] << endl;
            ret = hashmap.find ( data[i] )->second;
            i++;
        }
        //
    }

    //making hashtable null to be used for next iteration
    void make_root_null() {
        for ( int i = 0; i < s; i++ ) {
            hashmap.clear();
        }
    }

    //function to calculate average of an array
    long avg ( long array[] ) {
        long sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }

    //driver function to generate, insert and search rb hash tree
    void random_runner() {
        clock_t start, end;
        long insert_array[10], search_array[10];
        //cout << "Experiment Running....." << endl;
        for ( int i = 0; i < 10; i++ ) {
            generate_random();
            start = clock();
            insert_random();
            end = clock();
            insert_array[i] = end - start;
            start = clock();
            search_random();
            end = clock();
            search_array[i] = end - start;
            make_root_null();
        }
        cout << avg ( insert_array ) << " " <<  avg ( search_array ) << endl;    
    }

};

}

int main()
{
    long n = 1000000;
    RBtree::utility* util = new RBtree::utility ( n );
    util->random_runner();
    return 0;
}