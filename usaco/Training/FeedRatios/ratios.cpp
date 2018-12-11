/*
ID: silxikys
PROG: ratios
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

int goals[3];
int mixtures[3][3];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}


bool compare(pair<int,int> f1, pair<int,int> f2) {
	if (f1.second == 0 || f2.second == 0) {
		if (f1.second == 0 && f2.second == 0) {
			return true;
		}
		return false;
	}
	else if (f1.second != 0 && f2.second != 0) {
		return (f1.first/gcd(f1.first,f1.second) == f2.first/gcd(f2.first,f2.second) && f1.second/gcd(f1.first,f1.second) == f2.second/gcd(f2.first,f2.second));
	}
}

int main() {
	t1 = gettime();
	ofstream fout("ratios.out");
	ifstream fin("ratios.in");

	for (int qwer = 0; qwer < 6; qwer++) {
	//input
	for (int i = 0; i < 3; i++) {
		fin >> goals[i];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			fin >> mixtures[i][j];
		}
	}

	pair<int,int> xy = make_pair(goals[0],goals[1]);
	pair<int,int> yz = make_pair(goals[1],goals[2]);
	pair<int,int> xz = make_pair(goals[0],goals[2]);


	int smallestSum = INT_MAX;
	int ans[3];
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 100; k++) {
				int x = i*mixtures[0][0]+j*mixtures[1][0]+k*mixtures[2][0];
				int y = i*mixtures[0][1]+j*mixtures[1][1]+k*mixtures[2][1];
				int z = i*mixtures[0][2]+j*mixtures[1][2]+k*mixtures[2][2];

				if (x >= goals[0] && y >= goals[1] && z >= goals[2]) {

					pair<int,int> txy = make_pair(x,y);
					pair<int,int> tyz = make_pair(y,z);
					pair<int,int> txz = make_pair(x,z);
					
					bool bxy = compare(xy,txy);
					bool byz = compare(yz,tyz);
					bool bxz = compare(xz,txz);
					//if (i == 1 && j == 1 && k == 1) {
					//	cout << x << endl << y << endl << z << endl;
					//}
					if (bxy && byz && bxz) {

						int sum = i + j + k;
						if (sum < smallestSum) {
							smallestSum = sum;
							ans[0] = i;
							ans[1] = j;
							ans[2] = k;
						}
					}
				}
			}
		}
	}
	//output
	if (smallestSum == INT_MAX) {
		cout << "NONE" << endl;
		fout << "NONE" << endl;
	}
	else {
		int goalRatio = (ans[0]*mixtures[0][0]+ans[1]*mixtures[1][0]+ans[2]*mixtures[2][0])/(goals[0]);
		cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << goalRatio << endl;
		fout << ans[0] << " " << ans[1] << " " << ans[2] << " " << goalRatio << endl;
	}
	}



	
	endProgram(t1);
	return 0;
}