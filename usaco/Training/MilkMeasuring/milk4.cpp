/*
ID: silxikys
PROG: milk4
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

int Q, P;
const int maxp = 101;
const int maxq = 20001;
int pails[maxp];
vector<int> answer;

bool canbesummed(vector<int> combo, int cq) //returns true if the number Q can be summed to by a linear combination of the numbers in the vector combo
{
	bool isasum[maxq];
	isasum[0] = true;
	for (int i = 1; i <= cq; i++) {
		isasum[i] = false;
	}
	for (int i = 1; i <= cq; i++) {
		for (int j : combo) {
			if (i - j >= 0) {
				isasum[i] = isasum[i] || isasum[i-j];
			}
		}
	}
	return isasum[cq];
}

void makeCombinations(int reqlength, int start, vector<int> combo = {}) {
	if (answer.size() != 0) {
		return;
	}
	if (combo.size() == reqlength) {
		//do stuff with combo vector
		/*
		for (int i: combo) {
			cout << i << ' ';
		} cout << '\n';
		*/
		int newq = Q;
		for (int i : combo) {
			newq -= i;
		}
		/*
		for (int i : combo) {
			cout << i << " ";
		}
		cout << newq << endl;
		cout << canbesummed(combo,newq) << endl;
		*/

		if (newq >= 0 && canbesummed(combo,newq)) {
			answer = combo;
			return;
		}
	}
	else {
		for (int i = start; i < P; i++) {
			combo.push_back(pails[i]);
			makeCombinations(reqlength,i+1,combo);
			combo.pop_back();
		}
	}
}

int main() {
	t1 = gettime();
	ofstream fout("milk4.out");
	ifstream fin("milk4.in");

	//input
	fin >> Q >> P;
	for (int i = 0; i < P; i++) {
		fin >> pails[i];
	}
	sort(pails,pails+P);

	//calculations
	
	for (int length = 1; length <= P; length++) {
		makeCombinations(length,0);
		if (answer.size() > 0) {
			break;
		}
	}

	//output
	cout << answer.size() << ' ';
	fout << answer.size() << ' ';
	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i];
		fout << answer[i];
		if (i == answer.size() - 1) {
			cout << '\n';
			fout << '\n';
		}
		else {
			cout << ' ';
			fout << ' ';
		}
	}
	

	/*
	vector<int> test = {3,5};
	cout << canbesummed(test,Q-3-5) << endl;
	vector<int> test2 = {5,7};
	cout << canbesummed(test2,Q-5-7) << endl;
	*/
	
	endProgram(t1);
	return 0;
}