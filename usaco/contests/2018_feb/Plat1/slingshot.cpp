/*
ID: silxikys
PROG: slingshot
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
#include <set>
using namespace std;

ofstream fout("slingshot.out");
ifstream fin("slingshot.in");

struct Slingshot
{
	int start;
	int end;
	int time;
};
struct Edge
{
	int other;
	int weight;
};
typedef pair<int,int> pii;

const int maxn = 100005;
const int maxx = 1000000;
const int INF = 1000000000;
int N, M;
Slingshot slingshots[maxn];
vector<Edge> adjacents[maxx];

int Dijkstra(int source, int end) {
	set<pii> q;
	vector<int> dist(maxx,INF);
	q.insert(make_pair(0,source));
	dist[source] = 0;
	while (!q.empty()) {
		pii tmp = *(q.begin());
		q.erase(q.begin());
		int u = tmp.second;
		/*
		if (u == end) {
			break;
		}
		*/
		for (Edge e: adjacents[u]) {
			int v = e.other;
			int weight = e.weight;
			if (dist[v] > dist[u] + weight) {
				if (dist[v] != INF) {
					q.erase(q.find(make_pair(dist[v],v)));
				}
				dist[v] = dist[u] + weight;
				q.insert(make_pair(dist[v],v));
			}
		}
	}
	return dist[end];
}

int main() 
{
	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		int xi, yi, ti;
		fin >> xi >> yi >> ti;
		slingshots[i] = {xi,yi,ti};
		adjacents[xi].push_back({yi,ti});
		adjacents[yi].push_back({xi,ti});
	}
	
	for (int i = 0; i < maxx; i++) {
		if (i != 0) {
			adjacents[i].push_back({i-1,1});
		}
		if (i != maxx - 1) {
			adjacents[i].push_back({i+1,1});
		}
	}
	
	for (int i = 0; i < M; i++) {
		int aj, bj; fin >> aj >> bj;
		int ans = Dijkstra(aj,bj);
		fout << ans << '\n';
	}



	return 0;
}