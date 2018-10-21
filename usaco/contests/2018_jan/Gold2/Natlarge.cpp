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
#include <deque>
using namespace std;

ofstream fout("atlarge.out");
ifstream fin("atlarge.in");

const int maxn = 100002;
const int INF = 999999999;
int N, K;
vector<int> adjacents[maxn];
vector<int> leafs;
int distFromK[maxn];
int farmerDist[maxn];
bool visited[maxn];
int numBadLeafs;

void updateDist(int v) {
	deque<int> deq = {v};
	farmerDist[v] = 0;
	numBadLeafs--;
	bool visited[maxn];
	memset(visited,0,sizeof(visited));
	while (!deq.empty()) {
		visited[deq.front()] = true;
		bool isLeaf = true;
		for (int i: adjacents[deq.front()]) {
			if (!visited[i]) {
				isLeaf = false;
			}
			if (!visited[i] && farmerDist[deq.front()] + 1 < farmerDist[i]) {
				deq.push_back(i);
				farmerDist[i] = farmerDist[deq.front()] + 1;
				
			}
		}
		if (isLeaf && farmerDist[deq.front()] <= distFromK[deq.front()] && deq.front() != v) {
			numBadLeafs--;
			cout << "OK" << '\n';
		}
		deq.pop_front();
	}
}

int main() 
{
	fin >> N >> K;
	for (int i = 0; i < N - 1; i++) {
		int a, b; fin >> a >> b;
		adjacents[a].push_back(b);
		adjacents[b].push_back(a);
	}
	deque<int> deq = {K};
	distFromK[K] = 0;
	while (!deq.empty()) {
		visited[deq.front()] = true;
		bool isLeaf = true;
		for (int i: adjacents[deq.front()]) {
			if (!visited[i]) {
				deq.push_back(i);
				distFromK[i] = distFromK[deq.front()] + 1;
				isLeaf = false;
			}
		}
		if (isLeaf) {
			leafs.push_back(deq.front());
		}
		deq.pop_front();
	}
	
	for (int i = 1; i <= N; i++) {
		farmerDist[i] = INF;
	}
	deque<pair<int,int>> leafDists;
	for (int i : leafs) {
		leafDists.push_back(make_pair(distFromK[i],i));
	}
	sort(leafDists.begin(),leafDists.end(),[] (const pair<int,int>& a, const pair<int,int>& b) {
		return a.first < b.first;
	});
	numBadLeafs = leafs.size();
	int numFarmers = 0;
	while (numBadLeafs > 0) {
		pair<int,int> p = leafDists.front();
		updateDist(p.second);
		leafDists.pop_front();
		numFarmers++;
	}
	/*
	for (int i = 1; i <= N; i++) {
		cout << farmerDist[i] << '\n';
	}
	*/

	cout << numFarmers << '\n';
	fout << numFarmers << '\n';

	return 0;
}