/*
ID: silxikys
PROG: race3
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

const int maxp = 51;
int numnodes = 0;

int nodes[50][50]; //directed graph adjacency matrix

void floodRecurse(vector<int> &ret, int curr, int end) {
	if (curr == end) {
		return;
	}
	for (int next = 0; next < numnodes; next++) {
		if (nodes[curr][next] == 1) {
			if (find(ret.begin(),ret.end(),next) == ret.end()) {
				ret.push_back(next);
				floodRecurse(ret, next, end);
			}
		}
	}
}

vector<int> floodFill(int start, int end) {
	vector<int> ret = {start};
	floodRecurse(ret, start, end);
	sort(ret.begin(),ret.end());
	return ret;
}



int main() {
	t1 = gettime();
	ofstream fout("race3.out");
	ifstream fin("race3.in");

	//input
	int n; fin >> n;
	while (n != -1) {
		while (n != -2) {
			nodes[numnodes][n] = 1;
			fin >> n;
		}
		numnodes++;
		fin >> n;
	}

	//algorithm: floodfill

	vector<int> unavoidables;
	for (int i = 1; i < numnodes - 1; i++) {
		vector<int> addBacks;
		for (int j = 0; j < numnodes; j++) {
			if (nodes[j][i] == 1) {
				addBacks.push_back(j);
				nodes[j][i] = 0;
			}
		}

		vector<int> newpath = floodFill(0,numnodes-1);
		if (newpath.size() != numnodes - 1) {
			unavoidables.push_back(i);
		}

		for (int j : addBacks) {
			nodes[j][i] = 1;
		}
	}

	vector<int> splitters;
	for (int i = 1; i < numnodes - 1; i++) {
		vector<int> v1 = floodFill(0,i);
		vector<int> v2 = floodFill(i,numnodes-1);

		if (v1.size() + v2.size() == numnodes + 1) {
			splitters.push_back(i);
		}
	}

	//output
	sort(unavoidables.begin(),unavoidables.end());
	sort(splitters.begin(),splitters.end());

	fout << unavoidables.size();
	if (unavoidables.size() > 0) {
		for (int i : unavoidables) {
			fout << " " << i;
		}
	}
	fout << "\n";
	fout << splitters.size();
	if (splitters.size() > 0) {
		for (int i : splitters) {
			fout << " " << i;
		}
	}
	fout << "\n";

	endProgram(t1);
	return 0;
}