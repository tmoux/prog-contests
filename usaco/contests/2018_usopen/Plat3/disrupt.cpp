/*
ID: silxikys
PROG: disrupt
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

ofstream fout("disrupt.out");
ifstream fin("disrupt.in");

int N, M;
const int maxn = 50005;
struct xtraPath
{
	int n1, n2, weight;
	bool operator<(const xtraPath& rhs) const {
		return weight < rhs.weight;
	}
} extras[maxn];
pair<int,int> paths[maxn];

struct Tree
{
	vector<int> adjacents[maxn];
	void link(int n1, int n2) {
		adjacents[n1].push_back(n2);
		adjacents[n2].push_back(n1);
	}
	void cut(int n1, int n2) {
		adjacents[n1].erase(remove(adjacents[n1].begin(),adjacents[n1].end(),n2));
		adjacents[n2].erase(remove(adjacents[n2].begin(),adjacents[n2].end(),n1));
	}
	void dfs(int node, bool visited[maxn], int& counter) {
		counter++;
		visited[node] = true;
		for (int i: adjacents[node]) {
			if (!visited[i]) {
				dfs(i,visited,counter);
			}
		}
	}
	bool isConnected() {
		bool visited[maxn];
		memset(visited,0,sizeof(visited));
		int counter = 0;
		dfs(0,visited, counter);
		return (counter == N);
	}	
};

int main() 
{
	fin >> N >> M;
	Tree tree;
	for (int i = 0; i < N-1; i++) {
		int p, q;
		fin >> p >> q;
		p--; q--;
		tree.link(p,q);
		paths[i] = {p,q};
	}
	for (int i = 0; i < M; i++) {
		int p, q, r; fin >> p >> q >> r;
		p--; q--;
		extras[i] = {p,q,r};
	}
	sort(extras,extras+M);
	for (int i = 0; i < N-1; i++) {
		int n1 = paths[i].first;
		int n2 = paths[i].second;
		tree.cut(n1,n2);
		for (int j = 0; j < M; j++) {
			tree.link(extras[j].n1,extras[j].n2);
			if (tree.isConnected()) {
				tree.adjacents[extras[j].n1].pop_back();
				tree.adjacents[extras[j].n2].pop_back();
				cout << extras[j].weight << '\n';
				fout << extras[j].weight << '\n';
				break;
			}
			tree.adjacents[extras[j].n1].pop_back();
			tree.adjacents[extras[j].n2].pop_back();
		}
		tree.link(n1,n2);
	}
	

	return 0;
}