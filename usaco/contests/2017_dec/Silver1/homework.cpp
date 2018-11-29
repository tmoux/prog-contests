/*
ID: silxikys
PROG: homework
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

ofstream fout("homework.out");
ifstream fin("homework.in");

const int maxn = 100000;
int N;
int minnum[maxn];
int totalsum[maxn];
int scores[maxn];

double score(int k) {
	return (double)(totalsum[k]-minnum[k])/(N - k - 1);
}

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> scores[i];
	}
	for (int i = N - 1; i >= 0; i--) {
		if (i == N - 1) {
			totalsum[i] = scores[i];
			minnum[i] = scores[i];
		}
		else {
			totalsum[i] = scores[i] + totalsum[i+1];
			minnum[i] = min(scores[i],minnum[i+1]);
		}
	}

	vector<int> ks;
	double maxscore = 0;
	for (int k = 1; k <= N - 2; k++) {
		double sc = score(k);
		if (sc > maxscore) {
			maxscore = sc;
			ks = {k};
		}
		else if (sc == maxscore) {
			ks.push_back(k);
		}

		cout << k << ' ' << score(k) << '\n';

	}


	
	sort(ks.begin(),ks.end());
	for (int k: ks) {
		cout << k << '\n';
		fout << k << '\n';
	}
	

	return 0;
}
