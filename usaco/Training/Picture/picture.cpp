/*
ID: silxikys
PROG: picture
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

const int maxn = 5005;
const int maxcoord = 20002;
struct Rectangle {
	int minx, miny, maxx, maxy;
} recs[maxn];
int N, perimeter = 0;

int MINX = 999999999;
int MINY = 999999999;
int MAXX, MAXY;

vector<int> leftevents[maxcoord];
int leftcount[maxcoord];

vector<int> rightevents[maxcoord];
int rightcount[maxcoord];

vector<int> upevents[maxcoord];
int upcount[maxcoord];

vector<int> downevents[maxcoord];
int downcount[maxcoord];


int main() {
	t1 = gettime();
	ofstream fout("picture.out");
	ifstream fin("picture.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		int a, b, c, d;
		fin >> a >> b >> c >> d;
		a += 10000;
		b += 10000;
		c += 10000;
		d += 10000;
		recs[i] = {a,b,c,d};

		MINX = min(MINX,a);
		MINY = min(MINY,b);
		MAXX = max(MAXX,c);
		MAXY = max(MAXY,d);

		leftevents[a].push_back(i);
		leftevents[c].push_back(i);
		rightevents[a].push_back(i);
		rightevents[c].push_back(i);
		upevents[b].push_back(i);
		upevents[d].push_back(i);
		downevents[b].push_back(i);
		downevents[d].push_back(i);
	}

	//leftcount
	for (int x = MINX; x <= MAXX; x++) {
		for (int i: leftevents[x]) {
			int add = -1;
			if (recs[i].minx == x) {
				add = 1;
			}
			for (int j = recs[i].miny; j <= recs[i].maxy; j++) {
				leftcount[j] += add;
				if (leftcount[j] == 1 && add == 1) {
					perimeter++;
				}
			}
		}
	}

	//rightcount
	for (int x = MAXX; x >= MINX; x--) {
		for (int i: rightevents[x]) {
			int add = -1;
			if (recs[i].maxx == x) {
				add = 1;
			}
			for (int j = recs[i].miny; j <= recs[i].maxy; j++) {
				rightcount[j] += add;
				if (rightcount[j] == 1 && add == 1) {
					perimeter++;
				}
				
			}
		}
	}

	//upcount
	for (int x = MAXY; x >= MINY; x--) {
		for (int i: upevents[x]) {
			int add = -1;
			if (recs[i].maxy == x) {
				add = 1;
			}
			for (int j = recs[i].minx; j <= recs[i].maxx; j++) {
				upcount[j] += add;
				if (upcount[j] == 1 && add == 1) {
					perimeter++;
				}
				
			}
		}
	}

	//downcount
	for (int x = MINY; x <= MAXY; x++) {
		for (int i: downevents[x]) {
			int add = -1;
			if (recs[i].miny == x) {
				add = 1;
			}
			for (int j = recs[i].miny; j <= recs[i].maxy; j++) {
				downcount[j] += add;
				if (downcount[j] == 1 && add == 1) {
					perimeter++;
				}
				
			}
		}
	}

	cout << perimeter << '\n';




	
	endProgram(t1);
	return 0;
}