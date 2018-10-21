/*
ID: silxikys
PROG: talent
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

struct Cow
{
	int w;
	int t;
};

ofstream fout("talent.out");
ifstream fin("talent.in");

const int maxn = 250;
const int maxw = 2000;
int N, W;
Cow cows[maxn+1];
int maxTalent[maxw+10];

int getScore(int t, int w) {
	return (int)(1000*(double)t/w);
}

int main() 
{
	fin >> N >> W;
	for (int i = 0; i < N; i++) {
		int wi, ti; fin >> wi >> ti;
		cows[i] = {wi,ti};
	}
	memset(maxTalent,-1,sizeof(maxTalent));
	maxTalent[0] = 0;
	int ans = -1;
	for (int i = 0; i < N; i++) {
		for (int k = maxw-cows[i].w-1; k >= 0; k--) {
			if (maxTalent[k] == -1) continue;
			maxTalent[k+cows[i].w] = max(maxTalent[k+cows[i].w],maxTalent[k]+cows[i].t);
			if (k+cows[i].w >= W) {
				ans = max(ans,getScore(maxTalent[k+cows[i].w],k+cows[i].w));
			}
		}
	}
	cout << ans << '\n';
	fout << ans << '\n';
	

	return 0;
}