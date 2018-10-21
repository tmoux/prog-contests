#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stdio.h>
using namespace std;

typedef long long ll;
typedef pair<ll,int> iPair;
struct Edge
{
	int other;
	ll weight;
};

const int maxn = 200005;
int n, m;
vector<pair<int,ll>> adjacents[maxn];
ll concertweight[maxn];
ll dist[maxn];

void Dijkstra() {
	set<pair<ll,int>> setds;
	for (int i = 1; i <= n; i++) {
		dist[i] = concertweight[i];
		setds.insert({dist[i],i});
	}
	while (!setds.empty()) {
		int u = setds.begin()->second;
		setds.erase(setds.begin());
		for (const auto& e: adjacents[u]) {
			int v = e.first;
			ll weight = e.second;
			if (dist[v] > dist[u] + weight) {
				setds.erase({dist[u],u});
				dist[v] = dist[u] + weight;
				setds.insert({dist[v],v});
			}
		}
	}
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	scanf("%d%d", &n, &m);
	int vi, ui; ll wi;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%I64d",&vi,&ui,&wi);
		wi *= 2;
		adjacents[vi].push_back({ui,wi});
		adjacents[ui].push_back({vi,wi});
	}
	
	for (int i = 1; i <= n; i++) {
		scanf("%I64d",&concertweight[i]);
		//cin >> concertweight[i];
	}
	
	//dijkstra
	Dijkstra();
	
	//output
	for (int i = 1; i <= n; i++) {
		printf("%I64d ", dist[i]);
	}
	puts("");
		
	return 0;
}