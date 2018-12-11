/*
ID: silxikys
PROG: rockers
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

const int maxl = 22;
int N, M, T;
int songlength[maxl];
int numSongs[maxl][maxl][maxl];

int dp(int currSong, int currDisk, int amtUsed) {
	if (currSong == N) {
		return numSongs[currSong][currDisk][amtUsed] = 0;
	}
	if (numSongs[currSong][currDisk][amtUsed] != 0) {
		return numSongs[currSong][currDisk][amtUsed];
	}
	int newamtUsed = amtUsed;
	int newcurrDisk = currDisk;
	bool foundNext = false;
	if (songlength[currSong] > T - amtUsed) {
		if (currDisk + 1 < M && songlength[currSong] <= T) {
			newamtUsed = songlength[currSong];
			newcurrDisk++;
			foundNext = true;
		}
	}
	else {
		newamtUsed = amtUsed + songlength[currSong];
		foundNext = true;
	}
	if (foundNext) {
		return numSongs[currSong][currDisk][amtUsed] = max(dp(currSong+1,currDisk,amtUsed), dp(currSong+1,newcurrDisk,newamtUsed)+1);
	}
	else {
		return numSongs[currSong][currDisk][amtUsed] = dp(currSong+1,currDisk,amtUsed);
	}
}


int main() {
	t1 = gettime();
	ofstream fout("rockers.out");
	ifstream fin("rockers.in");

	fin >> N >> T >> M;
	for (int i = 0; i < N; i++) {
		fin >> songlength[i];
	}

	int ans = dp(0,0,0);
	cout << ans << endl;
	fout << ans << endl;



	
	endProgram(t1);
	return 0;
}