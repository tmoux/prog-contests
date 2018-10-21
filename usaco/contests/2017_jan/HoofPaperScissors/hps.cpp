/*
ID: silxikys
PROG: hps
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream fout("hps.out");
ifstream fin("hps.in");

const int maxn = 100000;
int N;
int ps[maxn], hs[maxn], ss[maxn];


int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		char c; fin >> c;
		if (i == 0) {
			if (c == 'P') {
				ps[i] = 0;
				hs[i] = 0;
				ss[i] = 1;
			}
			if (c == 'H') {
				ps[i] = 1;
				hs[i] = 0;
				ss[i] = 0;
			}
			if (c == 'S') {
				ps[i] = 0;
				hs[i] = 1;
				ss[i] = 0;
			}
		}
		else {
			if (c == 'P') {
				ps[i] = ps[i-1] + 0;
				hs[i] = hs[i-1] + 0;
				ss[i] = ss[i-1] + 1;
			}
			if (c == 'H') {
				ps[i] = ps[i-1] + 1;
				hs[i] = hs[i-1] + 0;
				ss[i] = ss[i-1] + 0;
			}
			if (c == 'S') {
				ps[i] = ps[i-1] + 0;
				hs[i] = hs[i-1] + 1;
				ss[i] = ss[i-1] + 0;
			}
		}
	}

	int maxwins = 0;
	for (int i = 0; i < N; i++) {
		int pwins = ps[i] + max(hs[N-1]-hs[i],
								ss[N-1]-ss[i]);
		int hwins = hs[i] + max(ps[N-1]-ps[i],
								ss[N-1]-ss[i]);
		int swins = ss[i] + max(hs[N-1]-hs[i],
								ps[N-1]-ps[i]);
		maxwins = max(max(max(hwins,swins),pwins),maxwins);
	}
	cout << maxwins << '\n';
	fout << maxwins << '\n';

	return 0;
}