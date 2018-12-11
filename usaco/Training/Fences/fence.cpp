/*
ID: silxikys
PROG: fence
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
int F;
vector<int> adjacents[505];



int main() {
	t1 = gettime();
	ofstream fout("fence.out");
	ifstream fin("fence.in");

	fin >> F;
	int largestVertex = 0;
	for (int a = 0; a < F; a++) {
		int i, j; fin >> i >> j;
		adjacents[i].push_back(j);
		adjacents[j].push_back(i);

		if (i > largestVertex) {
			largestVertex = i;
		}
		if (j > largestVertex) {
			largestVertex = j;
		}
	}
	//sort vectors
	for (int i = 1; i <= largestVertex; i++) {
		sort(adjacents[i].begin(),adjacents[i].end());
	}
	//find start vertex
	int startVertex = 0;
	for (int i = 1; i <= largestVertex; i++) {
		if (adjacents[i].size() % 2 == 1) {
			startVertex = i;
			break;
		}
	}
	if (startVertex == 0) {
		startVertex = 1;
	}
	//loop through all vertices, find next vertex
	int currVertex = startVertex;
	for (int i = 0; i < F; i++) {
		cout << currVertex << endl;
		fout << currVertex << endl;
		//find next vertex
		int nextVertex = 0;
		for (int j: adjacents[currVertex]) {
			if (adjacents[j].size() % 2 == 0) {
				nextVertex = j;
				break;
			}
		}
		if (nextVertex == 0) {
			nextVertex = adjacents[currVertex][0];
		}
		//cout << nextVertex << endl;
		//delete that fence
		/*
		for (int j = 0; j < adjacents[currVertex].size(); j++) {
			if (adjacents[currVertex][j] == nextVertex) {
				adjacents[currVertex].erase(adjacents[currVertex].begin()+j);
				break;
			}
		}
		*/
		for (int j = 0; j < adjacents[nextVertex].size(); j++) {
			if (adjacents[nextVertex][j] == currVertex) {
				adjacents[nextVertex].erase(adjacents[nextVertex].begin()+j);
				break;
			}
		}

		currVertex = nextVertex;
	}
	cout << currVertex << endl;
	fout << currVertex << endl;

	
	endProgram(t1);
	return 0;
}