/*
ID: silxikys
PROG: money
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

long long cache[10001][26];
int coins[25];

long long combos(int n, int v) {
	if (n == 0) return 1;
	if (v <= 0 || n < 0) return 0; 
	//cout << n << " " << v << endl;
	if (cache[n][v] != -1) return cache[n][v];
	return cache[n][v] = combos(n-coins[v-1],v) + combos(n,v-1);
}


int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("money.out");
	ifstream fin("money.in");

	//grabs input sorts coins array
	int V, N; fin >> V >> N;
	for (int i = 0; i < V; i++) {
		fin >> coins[i];
	}
	sort(coins, coins+V);

	//fill cache
	for (int n = 0; n<10001;n++) {
		for (int v = 0; v <26;v++) {
			cache[n][v] = -1;
		}
	}



	//compute answer
	long long ans = combos(N,V);

	cout << ans << endl;
	fout << ans << endl;



	
	
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}