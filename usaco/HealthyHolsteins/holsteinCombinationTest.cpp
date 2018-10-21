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
vector<vector<int>> combinations;

void printVec(vector<int> vec) {
	for (int i = 0; i<vec.size();i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

int vecSum(vector<int> vec) {
	int sum = 0;
	for (int i = 0; i<vec.size();i++) {
		sum += vec[i];
	}
	return sum;
}

void subtract(vector<int>& testCow, vector<int> vitamin) {
	for (int i = 0; i< V;i++) {
		testCow[i] -= vitamin[i];
	}
}

bool done(vector<int> testCow) {
	for (int i = 0; i< V; i++) {
		if (testCow[i] > 0) return false;
	}
	return true;
}

void combinate(int n, int r, vector<int> prevSeq = vector<int> {}) {
	if (prevSeq.size() == r) {
		combinations.push_back(prevSeq);
	}
	else {
		for (int i = (prevSeq.size() == 0) ? 1:prevSeq[prevSeq.size()-1]+1; i <= n; i++) {
			prevSeq.push_back(i);
			combinate(n, r, prevSeq);
			prevSeq.pop_back();
		}
	}
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
	//creates list of all possible combinations
	for (int i = 1; i<=G;i++) {
		combinate(G,i);
	}
	//test all possible combinations
	vector<int> smallestSet(16,0);
	for (int i = 0; i<combinations.size();i++) {
		vector<int> testSet = combinations[i];
		vector<int> testCow = requirements;
		vector<int>& testCowRef = testCow;

		

		for (int j = 0; j<testSet.size();j++) {
			subtract(testCowRef, feedAmount[testSet[j]-1]);
		}
		//printVec(testSet);
		//cout << ":   " << done(testCow) << endl;
		if (done(testCow)) {
			smallestSet = testSet;
			break;
		}
	}




	//output
	cout << smallestSet.size() << " ";
	printVec(smallestSet);

	fout << smallestSet.size() << " ";
	for (int i = 0; i<smallestSet.size();i++) {
		fout << smallestSet[i];
		if (i<smallestSet.size()-1) {
			fout << " ";
		}
		else {
			fout << endl;
		}
	}
	cout << combinations.size() << endl;
	
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}