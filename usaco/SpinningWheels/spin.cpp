/*
ID: silxikys
PROG: spin
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


struct Wheel{
	int speed;
	int numWedges;
	pair<int,int> wedges[5];
	void addTime(int t) {
		for (int i = 0; i < numWedges; i++) {
			wedges[i].first = (wedges[i].first+speed*t) % 360;
		}
	}
};

Wheel wheelList[5];



int main() {
	t1 = gettime();
	ofstream fout("spin.out");
	ifstream fin("spin.in");

	for (int i = 0; i < 5; i++) {
		fin >> wheelList[i].speed;
		fin >> wheelList[i].numWedges;
		for (int j = 0; j < wheelList[i].numWedges;j++) {
			int a, b; fin >> a >> b; pair<int,int> w = make_pair(a,b);
			wheelList[i].wedges[j] = w;
		}
	}
	/*
	for (int i = 0; i < 5; i++) {
		Wheel w = wheelList[i];
		cout << w.speed << " " << w.numWedges << " ";
		for (int j = 0; j < w.numWedges;j++) {
			cout << w.wedges[j].first << " " << w.wedges[j].second << " ";
		}
		cout << endl;
	}
	*/

	for (int t = 0; t < 360; t++) {
		int count[360] = {0};
		for (int i = 0; i < 5; i++) {
			Wheel w = wheelList[i];
			w.addTime(t);
			for (int j = 0; j < w.numWedges; j++) {
				pair<int,int> p = w.wedges[j];
				for (int k = 0; k <= p.second; k++) {
					int ang = (p.first+k) % 360;
					count[ang]++;
					if (count[ang] == 5) {
						cout << t << endl;
						fout << t << endl;
						goto end;
					}
				}
			}
		}
	}
	cout << "none" << endl;
	fout << "none" << endl;


	end: ;
	endProgram(t1);
	return 0;
}