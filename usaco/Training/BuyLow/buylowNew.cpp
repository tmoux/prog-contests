/*
ID: silxikys
PROG: buylow
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

const int maxn = 5005;
int prices[maxn];
vector<vector<int>> most[maxn];



int main() {
	t1 = gettime();
	ofstream fout("buylow.out");
	ifstream fin("buylow.in");

	int N; fin >> N;
	for (int i = 1; i <= N; i++) {
		fin >> prices[i];
	} 

	for (int i = N; i > 0; i--) {
		vector<vector<int>> seqs = {{prices[i]}};
		//find max length
		int maxlength = 1;
		bool found = false;
		for (int j = i + 1; j <= N; j++) {
			if (prices[j] < prices[i]) {
				maxlength = max(maxlength,most[i][0].size());
				found = true;
			}
		}

		if (found) {
			seqs = {{}};
			for (int j = i + 1; j <= N; j++) {
				if (prices[j] < prices[i]) {
					if (most[i][0].size() == maxlength) {
						for (vector<int> v: most[i]) {
							vector<int> c; c.insert(c.begin(),prices[i]);
							seqs.push_back(c);
						}
					}
				}
			}
		}
		
		most[i] = seqs;
	}

	for (int i = 1; i <= N; i++) {
		cout << prices[i] << endl;
		for (vector<int> v: most[i]) {
			for (int j: v) {
				cout << j << " ";
			} cout << endl;
		} cout << endl << endl;
	}

	

	
	


	endProgram(t1);
	return 0;
}