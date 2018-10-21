/*
ID: silxikys
PROG: highcard
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

ofstream fout("highcard.out");
ifstream fin("highcard.in");

int N;
const int maxn = 50000;
int elsie[maxn];

int main() 
{
	fin >> N;
	int lastplayed = 2*N+1;
	int ans = 0;
	int nc = 0;
	for (int i = 0; i < N; i++) {
		fin >> elsie[i];
	}
	sort(elsie,elsie+N,greater<int>());

	for (int a = 0; a < N; a++) {
		int i = elsie[a];
		nc += lastplayed - i - 1;
		if (nc > 0) {
			nc--;
			ans++;
			//cout << i << '\n';
		}
		lastplayed = i;
	}

	cout << ans << '\n';
	fout << ans << '\n';

	return 0;
}