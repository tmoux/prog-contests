/*
ID: silxikys
PROG: piepie
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <deque>
#include <cstring>
using namespace std;

ofstream fout("piepie.out");
ifstream fin("piepie.in");

struct Pie
{
	int bRating;
	int eRating;
	bool isBessies;
	int index;

	bool operator<(const Pie& other) const {
		if (isBessies) {
			return (eRating < other.eRating);
		}
		return (bRating < other.bRating);
	}
	bool operator<(int i) {
		if (isBessies) {
			return (eRating < i);
		}
		return (bRating < i);
	}

};

ostream& operator<<(ostream& stream, const Pie& pie) {
		stream << pie.bRating << ' ' << pie.eRating << ' ' << pie.isBessies << ' ' << pie.index << '\n';
		return stream;
	}

const int maxn = 100000;
int N, D;
Pie bessies[maxn];
Pie elsies[maxn];
int mindist[2][maxn]; //0 is bessie, 1 is elsie
Pie outputs[maxn];
map<Pie, int> mapping;
int main() 
{
	//input
	fin >> N >> D;
	//memset(mindist,-1,sizeof(mindist));
	deque<Pie> deq;
	for (int i = 0; i < N; i++) {
		int brate, erate;
		fin >> brate >> erate;
		bessies[i] = {brate,erate,1};
		outputs[i] = {brate,erate,1};
	}
	for (int i = 0; i < N; i++) {
		int brate, erate;
		fin >> brate >> erate;
		elsies[i] = {brate,erate,0};
	}
	sort(bessies,bessies+N);
	sort(elsies,elsies+N);
	/*
	for (int i = 0; i < N; i++) {
		cout << bessies[i];
	}*/
	for (int i = 0; i < N; i++) {
		if (bessies[i].eRating == 0) {
			deq.push_back(bessies[i]);
			mindist[0][i] = 1;
		}
		mapping[bessies[i]] = i;
		bessies[i].index = i;
		if (elsies[i].bRating == 0) {
			deq.push_back(elsies[i]);
			mindist[1][i] = 1;
		}
		elsies[i].index = i;
	}
	/*
	for (int i = 0; i < N; i++) {
		cout << bessies[i];
	}*/

	while (deq.size() != 0) {
		Pie fi = deq.front();

		if (fi.isBessies) {
			Pie* lowPtr = lower_bound(elsies,elsies+N,fi.bRating-D);
			for (; lowPtr->bRating <= fi.bRating && (lowPtr-elsies) < N; lowPtr++) {
				if (mindist[1][lowPtr-elsies] == 0) {
					mindist[1][lowPtr-elsies] = mindist[0][fi.index] + 1;
					deq.push_back(*lowPtr);
				}
			}
		}
		else {
			Pie* lowPtr = lower_bound(bessies,bessies+N,fi.eRating-D);
			for (; lowPtr->eRating <= fi.eRating && (lowPtr-bessies) < N; lowPtr++) {
				if (mindist[0][lowPtr-bessies] == 0) {
					mindist[0][lowPtr-bessies] = mindist[1][fi.index] + 1;
					deq.push_back(*lowPtr);
				}
			}
		}
		deq.pop_front();
	}

	
	for (int i = 0; i < N; i++) {
		//cout << mindist[0][mapping[outputs[i]]] << '\n';
		if (mindist[0][mapping[outputs[i]]] > 0) {
			fout << mindist[0][mapping[outputs[i]]] << '\n';
		}
		else {
			fout << "-1\n";
		}
		

	}





	return 0;
}