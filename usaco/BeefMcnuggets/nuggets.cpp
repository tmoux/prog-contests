/*
ID: silxikys
PROG: nuggets
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
#include <deque>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

//globals
int N; 
int packages[10];
deque<pair<int,bool>> deq;
int largest = 0;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}


int main() {
	t1 = gettime();
	ofstream fout("nuggets.out");
	ifstream fin("nuggets.in");

	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> packages[i];
		largest = max(largest,packages[i]);
	}

	int divisor = 1;
	if (N > 1) {
		divisor = gcd(packages[0],packages[1]);
		for (int i = 2; i < N; i++) {
			divisor = gcd(divisor,packages[i]);
		}
	}
	if (divisor != 1) {
		cout << 0 << endl;
		fout << 0 << endl;
	}
	
	else {
		int ans = 0;
		int consecutive = 0;
		for (int i = 1; i < 100000; i++) {
			bool flag = false;
			if (i <= largest) {
				for (int j = 0; j < N; j++) {
					if (i-packages[j] == 0) {
						flag = true;
						break;
					}
					else if (i-packages[j] > 0) {
						if (deq[deq.size()-packages[j]].second == true) {
							flag = true;
							break;
						}
					}
				}
			}
			else {
				for (int j = 0; j < N; j++) {
					if (deq[deq.size()-packages[j]].second == true) {
						flag = true;
						break;
					}
				}
				deq.pop_front();
			}
			deq.push_back(make_pair(i,flag));
			if (!flag) {
				ans = i;
				consecutive = 0;
			}
			else {
				consecutive++;
				if (consecutive >= largest) {
					break;
				}
			}
			/*
			for (pair<int,bool> p: deq) {
				cout << p.first << " " << p.second << endl;
			}
			cout << endl;
			*/
		}
		cout << ans << endl;
		fout << ans << endl;
	}
	
	
	
	endProgram(t1);
	return 0;
}