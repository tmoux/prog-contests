/*
ID: silxikys
PROG: shuffle
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

ofstream fout("shuffle.out");
ifstream fin("shuffle.in");

const int maxn = 101;
int N;
int backtrack[maxn];
int cowpos[maxn];
int newpos[maxn];

int main() 
{
	fin >> N;
	for (int i = 1; i <= N; i++) {
		int an; fin >> an;
		backtrack[an] = i;
	}

	for (int i = 1; i <= N; i++) {
		fin >> cowpos[i];
	}
	for (int a = 0; a < 3; a++) {
		for (int i = 1; i <= N; i++) {
			newpos[backtrack[i]] = cowpos[i];
		}
		for (int i = 1; i <= N; i++) {
			cowpos[i] = newpos[i];
		}
	}

	for (int i = 1; i <= N; i++) {
		cout << cowpos[i] << '\n';
		fout << cowpos[i] << '\n';
	}

	return 0;
}