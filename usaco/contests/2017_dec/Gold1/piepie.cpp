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
using namespace std;

ofstream fout("piepie.out");
ifstream fin("piepie.in");

const int maxn = 100000;
pair<int,int> cows[2*maxn];
vector<int> visited;
int mindist[2*maxn];
int N, D;

int main() 
{
	fin >> N >> D;

	for (int i = 0; i < 2*N; i++) {
		mindist[i] = -1;
		visited.push_back(i);
	}

	deque<int> deq;
	for (int i = 0; i < 2*N; i++) {
		int a, b;
		fin >> a >> b;
		cows[i] = make_pair(a,b);
		if ((i < N && b == 0) || i >= N && a == 0) {
			deq.push_back(i);
			visited.erase(remove(visited.begin(),visited.end(),i),visited.end());
			mindist[i] = 1;
		}
	}


	while (deq.size() != 0) {
		int fi = deq.front();
		int start, end;
		if (fi < N) {
			start = N;
			end = 2*N;
		}
		else {
			start = 0;
			end = N;
		}
		vector<int> removes;
		for (int i: visited) {
			//cout << fi << ' ' << i << '\n';
			if (i >= start && i < end) {
				if ((fi < N && cows[fi].first >= cows[i].first && cows[fi].first <= cows[i].first+D) || 
					(fi >= N && cows[fi].second >= cows[i].second && cows[fi].second <= cows[i].second+D)) {
					deq.push_back(i);
					mindist[i] = mindist[fi] + 1;
					removes.push_back(i);
				}
			}			
		}
		for (int i: removes) {
			visited.erase(remove(visited.begin(),visited.end(),i),visited.end());
		}
		deq.pop_front();
	}	

	for (int i = 0; i < N; i++) {
		//cout << mindist[i] << '\n';
		fout << mindist[i] << '\n';
	}


	return 0;
}