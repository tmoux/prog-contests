/*
ID: silxikys
PROG: cbs
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

ofstream fout("cbs.out");
ifstream fin("cbs.in");

const int maxn = 50005, maxk = 10;
int pre[maxk][maxn], N, K;
int previous[maxk][maxn], curr[2*maxn+5];
int nsets[maxk][maxn];

int main()
{
	fin >> K >> N;
	memset(previous,-1,sizeof(previous));
	for (int i = 0; i < K; i++) {
		memset(curr,-1,sizeof(curr));
		string s; fin >> s;
		for (int j = 1; j <= N; j++) {
			pre[i][j] = s[j-1] == '(' ? 1 : -1;
			pre[i][j] += pre[i][j-1];
			previous[i][j] = curr[pre[i][j]+maxn-1];
			curr[pre[i][j]+maxn] = j;
		}
	}

	//calc answer
	map<vector<int>,pair<int,int>> mp;
	vector<int> orig(K,0);
	mp[orig] = {0,0};
	int ans = 0;
	//maps vector of prefix sums to last occurence/number of sets
	for (int i = 1; i <= N; i++) {
		vector<int> add(K);
		for (int j = 0; j < K; j++) {
			add[j] = pre[j][i];
		}
		if (mp.count(add)) {
			//check if valid
			pair<int,int>& lastSeen = mp[add];
			int worst = -1;
			for (int j = 0; j < K; j++) {
				worst = max(worst,previous[j][i]);
			}
			if (worst < lastSeen.first) {
				//cout << worst << '\n';
				//cout << lastSeen.first << ' ' << lastSeen.second << '\n';
				ans += ++lastSeen.second;
				//cout << i << ' ' << lastSeen.second << '\n';
			}
			else {
				lastSeen = {i,0};
			}
		}
		else {
			mp[add] = {i,0};
		}
	}
	cout << ans << '\n';
	fout << ans << '\n';

	return 0;
}