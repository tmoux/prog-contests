/*
ID: silxikys
PROG: holstein
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

int V;
vector<int> requirements;
int G;
vector<vector<int>> feedAmount;

vector<int> subtract(vector<int> testCow, vector<int> vitamin) {
	for (int i = 0; i< V;i++) {
		testCow[i] -= vitamin[i];
	}
	return testCow;
}

bool done(vector<int> testCow) {
	for (int i = 0; i< V; i++) {
		if (testCow[i] > 0) return false;
	}
	return true;
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("holstein.out");
	ifstream fin("holstein.in");
	
	fin >> V;
	for (int i = 0; i < V; i++) {
		int a; fin >> a; requirements.push_back(a);
	}
	fin >> G;
	for (int i = 0; i < G; i++) {
		vector<int> a;
		feedAmount.push_back(a);
		for (int j = 0; j < V; j++) {
			int b; fin >> b;
			feedAmount[i].push_back(b);
		}
	}


	for (int i = 0; i < G; i++) {
		for (int j = 0; j < V; j++) {
			cout << feedAmount[i][j] << " ";
		}
		cout << endl;
	}

	sort(feedAmount.begin(), feedAmount.end(), [](const std::vector< int >& a, const std::vector< int >& b){ return a[0] > b[0]; } );

	for (int i = 0; i < G; i++) {
		for (int j = 0; j < V; j++) {
			cout << feedAmount[i][j] << " ";
		}
		cout << endl;
	}

	vector<int> testCow(V);
	vector<int> ret;
	for (int i = 0; i < V; i++) {
		testCow[i] = requirements[i];
	}
	for (int i = 0; i < V; i++) {
		if (done(subtract(testCow,feedAmount[i]))) {
			int retIndex = 0;
		}
	}
	

	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}