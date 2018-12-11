/*
ID: silxikys
PROG: agrinet
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

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

const int MAXN = 100;
int N;
int dist[MAXN][MAXN];
int inTree[MAXN];
int treeSize;
int cost;



int main() {
	t1 = gettime();
	ofstream fout("agrinet.out");
	ifstream fin("agrinet.in");

	//grab input
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int a; fin >> a; dist[i][j] = a;
		}
	}

	//add first node
	inTree[0] = 1;

	for (int treeSize = 1; treeSize < N; treeSize++) {
		int nextDist = 100001;
		int nextNode;
		//look through all nodes that are not in the tree, find their minimum distance to the tree
		for (int i = 0; i < N; i++) {
			if (inTree[i] == 0) { //if node is not in the tree
				int minDistance = 1000001;
				for (int j = 0; j < N; j++) {
					if (inTree[j] == 1 && dist[i][j] < minDistance) {
						minDistance = dist[i][j];
					}
				}
				if (minDistance < nextDist) {
					nextDist = minDistance;
					nextNode = i;
				}
			}
		}
		inTree[nextNode] = 1;
		cost += nextDist;
	}


	//output
	cout << cost << endl;
	fout << cost << endl;


	
	endProgram(t1);
	return 0;
}