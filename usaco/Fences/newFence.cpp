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
int adjacents[505][505];
int largestVertex = 0;
vector<int> stack;

void find(int i) {
	for (int j = 1; j <= largestVertex; j++) {
		while (adjacents[i][j] > 0) {
			adjacents[i][j]--;
			adjacents[j][i]--;
			find(j);
		}
	}
	stack.push_back(i);
}

int countDegree(int i) {
	int ret = 0;
	for (int j = 1; j <= largestVertex; j++) {
		ret += adjacents[i][j];
	}
	return ret;
}



int main() {
	t1 = gettime();
	ofstream fout("fence.out");
	ifstream fin("fence.in");

	fin >> F;
	for (int a = 0; a < F; a++) {
		int i, j; fin >> i >> j;
		adjacents[i][j]++;
		adjacents[j][i]++;

		if (i > largestVertex) {
			largestVertex = i;
		}
		if (j > largestVertex) {
			largestVertex = j;
		}
	}
	/*
	for (int i = 1; i <= largestVertex; i++) {
		for (int j = 1; j <= largestVertex; j++) {
			cout << adjacents[i][j] << " ";
		}
		cout << endl;
	}
	*/
	//find start vertex
	int startVertex = 0;
	for (int i = 1; i <= largestVertex; i++) {
		if (countDegree(i) % 2 == 1) {
			startVertex = i;
			break;
		}
	}
	if (startVertex == 0) {
		startVertex = 1;
	}
	
	find(startVertex);

	for (int i = stack.size()-1; i >= 0; i--) {
		//cout << stack[i] << endl;
		fout << stack[i] << endl;
	}
	

	

	
	endProgram(t1);
	return 0;
}