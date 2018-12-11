/*
ID: silxikys
PROG: shopping
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

struct offer {
	int numproducts[1005];
	int price;
};

int minPrice[6][6][6][6][6];
offer offerList[110];
int offerCounter;
int goalCode[6];
int goal[6];

int lowestCost(int a, int b, int c, int d, int e) {
	if (a < 0 || b < 0 || c < 0 || d < 0 || e < 0) {
		return INT_MAX;
	}
	if (a + b + c + d + e == 0) {
		return 0;
	}
	if (minPrice[a][b][c][d][e] != 0) {
		return minPrice[a][b][c][d][e];
	}
	int mini = INT_MAX;
 	for (int i = 0; i < offerCounter; i++) {
 		offer off = offerList[i];
 		int aq = a - off.numproducts[goalCode[0]];
 		int bq = b - off.numproducts[goalCode[1]];
 		int cq = c - off.numproducts[goalCode[2]];
 		int dq = d - off.numproducts[goalCode[3]];
 		int eq = e - off.numproducts[goalCode[4]];

 		if (aq >= 0 && bq >= 0 && cq >= 0 && dq >= 0 && eq >= 0) {
 			mini = min(mini, lowestCost(aq,bq,cq,dq,eq) + off.price);
 		}
 	}
 	//cout << mini << endl;
 	return minPrice[a][b][c][d][e] = mini;
}


int main() {

	t1 = gettime();
	ofstream fout("shopping.out");
	ifstream fin("shopping.in");



	//input
	
	int s, n, c, k, p; fin >> s;
	
	for (offerCounter = 0; offerCounter < s; offerCounter++) {
		offerList[offerCounter] = offer{};

		fin >> n;
		for (int j = 0; j < n; j++) {
			fin >> c >> k;
			offerList[offerCounter].numproducts[c] = k;

		}
		fin >> p;
		offerList[offerCounter].price = p;
	}


	int b; fin >> b;
	
	int goalCounter = 0;
	for (; offerCounter < b+s; offerCounter++) {
		fin >> c >> k >> p;
		offerList[offerCounter] = offer{};
		offerList[offerCounter].numproducts[c] = 1;
		offerList[offerCounter].price = p;

		goal[goalCounter] = k;
		goalCode[goalCounter] = c;
		goalCounter++;
	}

	//
	/*
	for (int i = 0; i < offerCounter; i++) {
		offer off = offerList[i];
		for (int j = 0; j < 10; j++) {
			cout << off.numproducts[j] << " ";
		}
		cout << off.price << endl << endl;
	}


	for (int i = 0; i < goalCounter; i++) {
		cout << goal[i] << endl;
	}
	*/

	
	int ans = lowestCost(goal[0],goal[1],goal[2],goal[3],goal[4]);

	cout << ans << endl;
	fout << ans << endl;
	




	
	endProgram(t1);
	return 0;
}