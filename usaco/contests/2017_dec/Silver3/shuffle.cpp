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

const int maxn = 100001;
bool isCycle[maxn];
bool visited[maxn];
bool currCycle[maxn];
vector<int> ancestors[maxn];
int N;

void dfs(int i) {
	if (visited[i]) return;
	visited[i] = true;
	currCycle[i] = true;
	bool cycle = false;
	for (int anc: ancestors[i]) {
		if (!visited[anc]) {
			dfs(anc);
		}
		if (currCycle[anc]) {
			cycle = true;
		}
		if (isCycle[anc]) {
			cycle = true;
		}
	}
	isCycle[i] = cycle;
	currCycle[i] = false;
}

int main() 
{
	fin >> N;
	for (int i = 1; i <= N; i++) {
		int an; fin >> an;
		ancestors[an].push_back(i);
	}


	int ans = 0;
	for (int i = 1; i <= N; i++) {
		dfs(i);
		if (isCycle[i]) {
			ans++;
		}
	}

	cout << ans << '\n';
	fout << ans << '\n';



	return 0;
}