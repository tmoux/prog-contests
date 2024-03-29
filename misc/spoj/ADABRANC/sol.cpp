/*
ID: silxikys
PROG: mootube
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

struct Edge
{
	int a;
	int b;
	int relevance;

	bool operator<(const Edge& rhs) const
	{
		if (relevance != rhs.relevance) {
			return relevance > rhs.relevance;
		}
		return false;
	}
};

struct Query
{
	int ki;
	int vi;
	int idx;

	bool operator<(const Query& rhs) const
	{
		if (ki != rhs.ki) {
			return ki > rhs.ki;
		}
		return false;
	}
};

const int maxn = 100005;
int N, M, Q;
int parent[maxn];
Edge edges[maxn];
Query que[maxn]; 
int answers[maxn];
int idx;

int Find(int node) {return parent[node] < 0 ? node : (parent[node] = Find(parent[node]));}

void Union(int x, int y) 
{
	x = Find(x);
	y = Find(y);
	if (x == y) return;
	if (parent[x] > parent[y]) {
		swap(x,y);
	}
	parent[x] += parent[y];
	parent[y] = x;
}

int ansQuery(int ki, int vi)
{
	while (idx < N - 1 && edges[idx].relevance >= ki) {
		Union(edges[idx].a,edges[idx].b);
		idx++;
	}
	return -parent[Find(vi)];
}

int main() 
{	
	#ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
	for (int i = 0; i <= maxn; i++) {
		parent[i] = -1;
	}
	cin >> N >> M >> Q;
	for (int i = 0; i < M; i++) {
		int pi, qi, ri; cin >> pi >> qi >> ri;
		edges[i] = {pi, qi, ri};
	}
	sort(edges,edges+N-1);
	int kii, vii;
	for (int i = 0; i < Q; i++) {
		cin >> kii >> vii;
		que[i] = {kii,vii,i};
	}
	sort(que, que + Q);
	for (int i = 0; i < Q; i++) {
		Query p = que[i];
		int ans = ansQuery(p.ki,p.vi);
		answers[p.idx] = ans;
	}
	for (int i = 0; i < Q; i++) {
		cout << answers[i] << '\n';
	}
	return 0;
}