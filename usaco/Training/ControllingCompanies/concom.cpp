/*
ID: silxikys
PROG: concom
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
#include <cstring>
using namespace std;
using namespace std::chrono;

//globals
int N;
int own[101][101];
int controls[101][101]; //0 means no, 1 means yes

void findControl(int i) {
	int numFound = 0;
	for (int j = 1; j<101;j++) {
		if (controls[i][j] != 1) {
			int sum = 0;
			for (int k = 1; k<101;k++) {
				if (controls[i][k] == 1) {
					sum += own[k][j];
				}				
			}
			if (sum > 50) {
				controls[i][j] = 1;
				numFound++;
			}
				
		}
	}
	//cout << i << " " << numFound << endl;
	if (numFound > 0) {
		findControl(i);
	}
}


int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("concom.out");
	ifstream fin("concom.in");

	//zero out own/controls array
	memset(own, 0, sizeof(own[0][0] * 101*101));
	memset(controls, 0, sizeof(controls[0][0] * 101*101));
	//add that every company controls itself
	for (int i = 0; i<101;i++) {
		controls[i][i] = 1;
	}

	fin >> N;
	//input data goes into own array
	for (int a = 0; a<N;a++) {
		int i, j, p; fin >> i >> j >> p;
		own[i][j] = p;
	}

	//does calculation
	for (int i = 1; i<101;i++) {
		findControl(i);
	}
	 //ouputs controls array
	/*
	for (int i = 1; i<101;i++) {
		for (int j = 1; j<101;j++) {
			cout << controls[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
	

	for (int i = 1; i<101;i++) {
		for (int j = 1; j<101;j++) {
			if (i != j && controls[i][j] == 1) {
				cout << i << " " << j << endl;
				fout << i << " " << j << endl;
			}
		}
	}




	
	
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}