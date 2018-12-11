/*
ID: silxikys
PROG: job
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




int main() {
	t1 = gettime();
	ofstream fout("job.out");
	ifstream fin("job.in");

	int N, M1, M2;
	const int maxn = 1000;
	const int maxm = 30;
	fin >> N >> M1 >> M2;

	int m1time[maxm], m2time[maxm];
	for (int i = 0; i < M1; i++) {
		fin >> m1time[i];
	}
	for (int i = 0; i < M2; i++) {
		fin >> m2time[i];
	}

	int atime = 0;
	vector<int> M1finish(M1,0), taskA(N,0);
	for (int j = 0; j < N; j++) {
		int minfinish = 99999, index = -1;
		for (int i = 0; i < M1; i++) {
			if (M1finish[i] + m1time[i] < minfinish) {
				minfinish = M1finish[i] + m1time[i];
				index = i;
			}
		}
		M1finish[index] += m1time[index];
		atime = M1finish[index];
		taskA[j] = minfinish;
	}

	vector<int> M2finish(M2,0), taskB(N,0);
	for (int j = N-1; j >= 0; j--) {
		int minfinish = 99999, index = -1;
		for (int i = 0; i < M2; i++) {
			if (M2finish[i] + m2time[i] < minfinish) {
				minfinish = M2finish[i] + m2time[i];
				index = i;
			}
		}
		M2finish[index] += m2time[index];
		taskB[j] = minfinish;
	}

	int total = 0;
	for (int i = 0; i < N; i++) {
		if (taskA[i] + taskB[i] > total) {
			total = taskA[i] + taskB[i];
		}
	}

	cout << atime << " " << total << endl;
	fout << atime << " " << total << endl;
	
	endProgram(t1);
	return 0;
}