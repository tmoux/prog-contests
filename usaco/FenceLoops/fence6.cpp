/*
ID: silxikys
PROG: fence6
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
vector<vector<int>> adjacents;
int N;
int edgelength[105];
int length[105][105];



int main() {
	t1 = gettime();
	ofstream fout("fence6.out");
	ifstream fin("fence6.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		int s, ls, n1, n2;
		fin >> s >> ls >> n1 >> n2;
		edgelength[s] = ls;
		vector<int> v1 = {s}, v2 = {s};
		for (int j = 0; j < n1; j++) {
			int k; fin >> k;
			v1.push_back(k);
		}
		for (int j = 0; j < n2; j++) {
			int k; fin >> k;
			v2.push_back(k);
		}
		sort(v1.begin(),v1.end()); sort(v2.begin(),v2.end());
		//add these vertices if not already in adjacents
		bool v1flag = true, v2flag = true;
		for (vector<int> q: adjacents) {
			if (q == v1) {
				v1flag = false;
				break;
			}
		}
		for (vector<int> q: adjacents) {
			if (q == v2) {
				v2flag = false;
				break;
			}
		}
		if (v1flag) {
			adjacents.push_back(v1);
		}
		if (v2flag) {
			adjacents.push_back(v2);
		}
	}	

	vector<vector<int>> adj(adjacents.size());
	for (int i = 0; i < adjacents.size(); i++) {
		vector<int> v = adjacents[i];
		
	}

	//for each vertex and one of its adjacent vertices, remove the included edge and run dijkstra to find the shortest path between the two vertices. then add back the distance of the removed edge, and compare this with the smallest distance calculated so far




	
	endProgram(t1);
	return 0;
}