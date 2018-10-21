/*
ID: silxikys
PROG: inflate
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
int M, N;
pair<int, int> categories[10000];
int best[100001];

bool pairCompare(const pair<int, int>& a, const pair<int,int>& b) {
  return (double) a.first/a.second > (double) b.first/b.second;
}

int main() {
	t1 = gettime();
	ofstream fout("inflate.out");
	ifstream fin("inflate.in");

	//input
	fin >> M >> N;
	for (int i = 0; i < N; i++) {
		int a, b; fin >> a >> b;
		pair<int,int> p = make_pair(a,b);
		categories[i] = p;
	}

	sort(categories,categories+N,pairCompare);
	//for (int i = 0; i < N; i++) {
	//	cout << categories[i].first << " " << categories[i].second << endl;
	//}

	for (int i = 0; i < N; i++) {
		pair<int, int> p = categories[i];
		for (int j = 0; j+p.second <= M; j++) {
			if (best[j]+p.first > best[j+p.second]) {
				best[j+p.second] = best[j]+p.first;
			}
		}
	}

	cout << best[M] << endl;
	fout << best[M] << endl;




	
	endProgram(t1);
	return 0;
}