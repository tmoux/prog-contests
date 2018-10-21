/*
ID: silxikys
PROG: newbarn
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
#include <queue>
using namespace std;

ofstream fout("newbarn.out");
ifstream fin("newbarn.in");

const int maxq = 100001;
int Q;
vector<int> adjacents[maxq];
bool visited[maxq];
int numBarns = 1;
void update(int p) {
	if (p != -1) {
		adjacents[p].push_back(numBarns);
		adjacents[numBarns].push_back(p);
	}
	numBarns++;
}

void dfs(int p, int count, int& maxdepth) {
	visited[p] = true;
	maxdepth = max(maxdepth,count);
	for (int i: adjacents[p]) {
		if (!visited[i]) {
			dfs(i,count+1,maxdepth);
		}
	}
}

void query(int p) {
	memset(visited,0,sizeof(visited));
	int maxdepth = 0;
	dfs(p,0,maxdepth);
	//cout << maxdepth << '\n';
	fout << maxdepth << '\n';
}

int main() 
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	fin >> Q;
	for (int i = 0; i < Q; i++) {
		char c; int p;
		fin >> c >> p;
		switch (c) {
			case 'B':
				update(p);
				break;
			case 'Q':
				query(p);
		}
	}

	return 0;
}