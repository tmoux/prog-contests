/*
ID: silxikys
PROG: superbull
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;

ofstream fout("superbull.out");
ifstream fin("superbull.in");

const int maxn = 2000;
int N;
int xors[maxn];
int combos[maxn*maxn];

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> xors[i];
	}
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			combos[i*maxn+j] = (xors[i] ^ xors[j]);
		}
	}
	sort(combos,combos+maxn*maxn,greater<int>());
	long long total = 0;
	int count = 1;
	for (auto a = 0; a < N - 1 && count < N; a++) {
		//cout << a.second.first << ' ' << a.second.second << ' ' << a.first << '\n';
		total += combos[a];
		count++;
	}
	cout << total << '\n';
	fout << total << '\n';

	return 0;
}