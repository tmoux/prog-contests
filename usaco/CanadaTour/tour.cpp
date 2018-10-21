/*
ID: silxikys
PROG: tour
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

//globals
int N, V;
const int maxn = 101;
const int neginf = -99999;
bool isflight[maxn][maxn];
map<string,int> cityint;
int dp[maxn][maxn];

int maxFlight(int i, int j) {
	//cout << i << ' ' << j << '\n';
	if (dp[i][j]) {
		return dp[i][j];
	}
	if (i == N - 1 && j == N - 1) {
		return dp[i][j] = 1;
	}
	if (i == j && i > 0 && j < N - 1) {
		return dp[i][j] = neginf;
	}
	int maxcities;
	if (i == j && i == 0) {
		maxcities = 1;
	}
	else {
		maxcities = neginf;
	}
	if (i <= j) {
		for (int u = i+1; u < N; u++) {
			if (isflight[i][u]) {

				maxcities = max(maxcities,maxFlight(u,j) + 1);
			}
		}
	}
	else {
		for (int u = j+1; u < N; u++) {
			if (isflight[j][u]) {
				maxcities = max(maxcities,maxFlight(i,u) + 1);
			}
		}
	}

	if (i == j && i == 0 && maxcities != 1) {
		maxcities--;
	}
	return dp[i][j] = maxcities;
}

int main() {
	t1 = gettime();
	ofstream fout("tour.out");
	ifstream fin("tour.in");

	//input
	fin >> N >> V;
	for (int i = 0; i < N; i++) {
		string s; fin >> s;
		cityint[s] = i;
	}
	for (int i = 0; i < V; i++) {
		string s, t; fin >> s >> t;
		isflight[cityint[s]][cityint[t]] = 1;
		isflight[cityint[t]][cityint[s]] = 1;
	}
	/*
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << isflight[i][j] << ' ';
		} cout << '\n';
	}
	*/
	int ans = maxFlight(0,0);
	cout << ans << endl << endl;
	fout << ans << endl;

	/*
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << dp[i][j] << ' ';
		} cout << '\n';
	}
	*/
	
	endProgram(t1);
	return 0;
}