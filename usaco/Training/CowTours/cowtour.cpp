/*
ID: silxikys
PROG: cowtour
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
#include <iomanip>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1, t2;

struct Point {
	int x;
	int y;
};
//globals
int N;
Point pastures[150];
char adjacents[150][150];
double sp[150][150];
int components[150];
int numComponents = 0;
vector<vector<int>> compList;

double distance(Point a, Point b) {
	return pow(pow(a.x-b.x,2)+pow(a.y-b.y,2),0.5);
}

void floodFill(int j) {
	components[j] = numComponents;
	for (int k = 0; k < N; k++) {
		if (adjacents[j][k] == '1' && components[k] == 0) {
			floodFill(k);
		}
	}
}

void beginFill() {
	for (int i = 0; i < N; i++) {
		if (components[i] == 0) {
			numComponents++;
			components[i] = numComponents;  
			for (int j = 0; j < N; j++) {
				if (adjacents[i][j] == '1' && components[j] == 0) {
					floodFill(j);
				}
			}
		}
	}
}

double diameter(vector<int> comp) {
	//double sp[150][150];
	for (int i : comp) {
		for (int j : comp) {
			if (adjacents[i][j] == '1') {
				sp[i][j] = distance(pastures[i],pastures[j]);
			}
			else if (adjacents[i][j] == '0') {
				sp[i][j] = INT_MAX;
			}
		}
	}
	for (int k: comp) {
		for (int i : comp) {
			for (int j : comp) {
				if (sp[i][k] + sp[k][j] < sp[i][j]) {
					sp[i][j] = sp[i][k] + sp[k][j];
				}
			}
		}
	}
	double d = 0;
	for (int i: comp) {
		for (int j : comp) {
			if (i != j && sp[i][j] > d) {
				d = sp[i][j];
			}
		}
	}
	/*
	for (int i: comp) {
		for (int j: comp) {
			cout << sp[i][j] << " ";
		}
		cout << endl;
	}
	*/
	return d;
}


int main() {
	t1 = gettime();
	ofstream fout("cowtour.out");
	ifstream fin("cowtour.in");

	//fill components with 0
	for (int i = 0; i < N; i++) {
		components[i] = 0;
	}
	//grab input
	fin >> N;
	for (int i = 0; i < N; i++) {
		int x, y; fin >> x >> y;
		Point p = {x,y};
		pastures[i] = p;
	}
	string line;
	for (int i = 0; i < N; i++) {
		fin >> line;
		for (int j = 0; j < N; j++) {
			adjacents[i][j] = line[j];
		}
	}
	//floyd-warshall
	/*
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (adjacents[i][j] == '1') {
				sp[i][j] = distance(pastures[i],pastures[j]);
			}
			else if (adjacents[i][j] == '0') {
				sp[i][j] = INT_MAX; //make sure that all distances are>0
			}
		}
	} 

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (sp[i][k] + sp[k][j] < sp[i][j]) {
					sp[i][j] = sp[i][k] + sp[k][j];
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << fixed << setprecision(1) <<min(sp[i][j],100.0) << " ";

		}
		cout << endl;
	}
	*/
	//put all pastures into components
	beginFill();
	//create compList
	compList.push_back(vector<int> {});
	for (int i = 1; i <= numComponents; i++) {
		compList.push_back(vector<int> {});
		for (int j = 0; j < N; j++) {
			if (components[j] == i) {
				compList[i].push_back(j);
			}
		}
	}
	/* Printing out the component
	for (int i = 1; i < compList.size();i++) {
		for (int j: compList[i]) {
			cout << j << " ";
		}

	}
	*/
	//
	double min = INT_MAX;
	for (int i = 0; i < N-1; i++) {
		for (int j = i+1; j < N; j++) { 
			if (adjacents[i][j] == '0' && components[i] != components[j]) {
				
				adjacents[i][j] = '1';
				adjacents[j][i] = '1';
				vector<int> newVec = compList[components[i]];
				newVec.insert(newVec.end(),compList[components[j]].begin(), compList[components[j]].end());
				//for (int i: newVec) {
				//	cout << i << " ";
				//}
				double dia = diameter(newVec);
				if (dia < min) {
					min = dia;
				}

				adjacents[i][j] = '0';
				adjacents[j][i] = '0';				
			}
		}
	}

	cout << fixed << setprecision(6) << min << endl;
	fout << fixed << setprecision(6) << min << endl;


	

	




	//for output use cout << fixed << setprecision(6) << double;
	endProgram(t1);
	return 0;
}