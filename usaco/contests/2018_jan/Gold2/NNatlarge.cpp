/*
ID: silxikys
PROG: atlarge
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

ofstream fout("atlarge.out");
ifstream fin("atlarge.in");

const int INF = 999999;
const int maxn = 100002;
int N, K;
vector<int> adjacents[maxn];
queue<int> leafs;
int distFromLeaf[maxn], bessieDist[maxn];
bool bessieVisited[maxn];
int main() 
{
	fin >> N >> K;
	for (int i = 0; i < maxn; i++) {
		distFromLeaf[i] = INF;
	}
	//input
	for (int i = 0; i < N- 1; i++) {
		int a, b; fin >> a >> b;
		adjacents[a].push_back(b);
		adjacents[b].push_back(a);
	}
	//find leafs
	for (int i = 1; i <= N; i++) {
		if (adjacents[i].size() == 1) {
			leafs.push(i);
			distFromLeaf[i] = 0;
		}
	}
	//bfs to determine min distance from leaf
	while (!leafs.empty()) {
		for (int adj: adjacents[leafs.front()]) {
			if (distFromLeaf[adj] > distFromLeaf[leafs.front()] + 1) {
				leafs.push(adj);
				distFromLeaf[adj] = distFromLeaf[leafs.front()] + 1;
			}
		}
		leafs.pop();
	}
	//bfs from Bessie's start
	//if Bessie's distance[i] is >= than distFromLeaf[i], then a farmer can reach it faster than she can, so we add a farmer and do not push any adjacents of i
	int numFarmers = 0;
	queue<int> bessieQ;
	bessieQ.push(K);
	bessieDist[K] = 0;
	while (!bessieQ.empty()) {
		int n = bessieQ.front();
		bessieVisited[n] = true;
		if (bessieDist[n] >= distFromLeaf[n]) {
			numFarmers++;
		}
		else {
			for (int adj: adjacents[n]) {
				if (!bessieVisited[adj]) {
					bessieQ.push(adj);
					bessieDist[adj] = bessieDist[n] + 1;
				}
			}
		}
		bessieQ.pop();
	}
	//output
	cout << numFarmers << '\n';
	fout << numFarmers << '\n';



	return 0;
}