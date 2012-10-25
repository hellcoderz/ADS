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

class utility
{
public:
    MAP* hashTable;
    int s;
    long n;
    long* data;

    utility ( int n, int s ) {
        this->s = s;
        this->n = n;
        data = new long[n];
        hashTable = new MAP[s];
    }

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
        while ( i < n / 2 ) {
            r = rand() % n;
            //cout << r << "->" << i << endl;
            temp = data[r];
            data[r] = data[n - r - 1];
            data[n - r - 1] = temp;
            i++;
        }
    }

    void insert_random() {
        long i = 0;
        while ( i < n ) {
            //cout << "Inserting = " << data[i] <<  endl;
            hashTable[data[i] % s].insert ( PAIR ( data[i], 2 * data[i] ) );
            i++;
        }
    }

    void search_random() {
        long int i = 0;
        long ret;
        while ( i < n ) {
            //cout << "Searching " << data[i] << endl;
            ret = hashTable[data[i] % s].find ( data[i] )->second;
            i++;
        }
        //
    }

    void make_root_null() {
        for ( int i = 0; i < s; i++ ) {
            hashTable[i].clear();
        }
    }

    long avg ( long array[] ) {
        long sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += array[i];
        }
        return sum / 10;
    }

    void random_runner() {
        clock_t start, end;
        long insert_array[10], search_array[10];
        cout << "Experiment Running....." << endl;
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
        cout << "Insert Avg. Time : " << avg ( insert_array ) << "   " << "Search Avg. Time : " << avg ( search_array ) << endl;
    }

};

}

int main()
{
    long n = 1000000;
    int s = 10;
    RBhash::utility* util = new RBhash::utility ( n, s );
    util->random_runner();
    return 0;
}