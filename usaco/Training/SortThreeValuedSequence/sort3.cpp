/*
ID: silxikys
PROG: sort3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

//globals
int N;
int list[1000];
int numOf[4];  
int i1, i2, i3;
int numSwaps = 0;

///////////////////////////////////
void printList() {
	for (int i = 0; i<N;i++) {
		cout << list[i] << " ";
		if (i == i3-1 || i == i2-1) {
			cout << " ";
		}
	}
	cout << endl;
}
////////////////////////////////////
int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("sort3.out");
	ifstream fin("sort3.in");
	
	fin >> N;
	
	for (int i = 0;i<4;i++) numOf[i] = 0;
	for (int i = 0; i<N;i++) {
		int v; fin >> v;
		list[i] = v;
		numOf[v]++;
	}
	i1 = 0, i2 = numOf[1], i3 = numOf[1] + numOf[2];
	cout << i1 << " " << i2 << " " << i3 << endl;

	printList();
	//swap 2s in part 1 with 1s in part 2
	for (int i = i1; i<i2;i++) {
		if (list[i] == 2) {
			for (int j = i2; j<i3; j++) {
				if (list[j] == 1) {
					//swap i and j
					list[i] = 1;
					list[j] = 2;
					numSwaps++;
					//printList();
					break;
				}

			}
		}
	}
	//swap 1s in part 3 with 3s in part 1
	for (int i = i1; i<i2;i++) {
		if (list[i] == 3) {
			for (int j = i3; j<N;j++) {
				if (list[j] == 1) {
					list[i] = 1;
					list[j] = 3;
					numSwaps++;
					//printList();
					break;
				}
			}
		}
	}
	//swap 3s in part 2 with 2s in part 3
	for (int i = i2; i<i3; i++) {
		if (list[i] == 3) {
			for (int j = i3; j<N;j++) {
				if (list[j] == 2) {
					list[i] = 2;
					list[j] = 3;
					numSwaps++;
					//printList();
					break;
				}
			}
		}
	}
	//now swap all the 1s
	for (int i = i1; i<i2;i++) {
		if (list[i] != 1) {
			for (int j = i2; j<N; j++) {
				if (list[j] == 1) {
					list[j] = list[i];
					list[i] = 1;
					numSwaps++;
					//printList();
					break;
				}
			}
		}
	}
	//now swaps all the 3s with 2s
	for (int i = i3; i < N; i++) {
		if (list[i] != 3) {
			for (int j = i1; j<i3;j++) {
				if (list[j] == 3) {
					list[j] = list[i];
					list[i] = 3;
					numSwaps++;
					//printList();
					break;
				}
			}
		}
	}

	cout << numSwaps << endl;
	fout << numSwaps << endl;

	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}