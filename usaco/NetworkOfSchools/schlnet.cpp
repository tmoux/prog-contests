/*
ID: silxikys
PROG: schlnet
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

//globals
const int maxn = 103;
int N;
int network[maxn][maxn]; 
//network[i][j] -> j is a child of i
int headOrTail[maxn]; //-2 = not seen, uninitialized, -1 = seen but uninitialized,
//0 = tail, 1 = head

void findHeadTail(int node) {
	if (headOrTail[node] >= 0) {
		return;
	}
	int numOfParents = 0;
	headOrTail[node] = -1;
	for (int parent = 1; parent <= N; parent++) {
		if (network[parent][node]) {
			if (headOrTail[parent] == 1 || headOrTail[parent] == 0) {
				//its a head/tail, dont bother recurse
				numOfParents++;
			}
			else if (headOrTail[parent] == -2) {
				numOfParents++;
				findHeadTail(parent);
			}
		}
	}
	if (numOfParents > 0) {
		headOrTail[node] = 0;
	}
	else if (numOfParents == 0) {
		headOrTail[node] = 1;
	}
}

int main() {
	t1 = gettime();
	ofstream fout("schlnet.out");
	ifstream fin("schlnet.in");

	fin >> N;
	for (int i = 1; i <= N; i++) {
		int child;
		while (true) {
			fin >> child;
			if (!child)
				break;
			network[i][child] = 1;
		}
	}
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << network[i][j] << ' ';
		} cout << '\n';
	}
	*/
	//identify heads and tails
	for (int i = 1; i <= N; i++)
		headOrTail[i] = -2;
	for (int i = 1; i <= N; i++) {
		findHeadTail(i);
		/*
		for (int i = 1; i <= N; i++) {
			cout << headOrTail[i] << ' ';
		} cout << '\n';
		*/
	}

	int taska = 0;
	for (int i = 1; i <= N; i++) {
		taska += headOrTail[i];
	}
	//subtask B
	int sources = 0, sinks = 0;
	for (int i = 1; i <= N; i++) {
		bool issource = true;
		for (int j = 1; j <= N; j++) {
			if (network[j][i] == 1) {
				issource = false;
				break;
			}
		}
		if (issource) {
			sources++;
		}
	}
	for (int i = 1; i <= N; i++) {
		bool issink = true;
		for (int j = 1; j <= N; j++) {
			if (network[i][j] == 1) {
				//cout << i << " " << j << '\n';
				issink = false;
				break;
			}
		}
		//cout << i << " " << issink << '\n';
		if (issink) {
			sinks++;
		}
	}
	cout << sources << " " << sinks << '\n';
	int numcycles = taska - sources;
	int taskb;
	if (numcycles == 1 && taska == 1 && sinks == 0) {
		taskb = 0;
	}
	else {
		taskb = max(taska, sinks);
	}


	cout << taska << '\n' << taskb << '\n';
	fout << taska << '\n' << taskb << '\n';
	
	endProgram(t1);
	return 0;
}