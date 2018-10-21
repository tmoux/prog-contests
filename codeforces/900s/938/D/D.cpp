#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

typedef long long ll;
typedef pair<ll,int> ii;
struct Edge
{
	int other;
	ll weight;
};

const int maxn = 200005;
vector<Edge> adjacents[maxn];
ll concertweight[maxn];


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int vi, ui; ll wi; cin >> vi >> ui >> wi;
		wi *= 2;
		adjacents[vi].push_back({ui,wi});
		adjacents[ui].push_back({vi,wi});
	}
	for (int i = 1; i <= n; i++) {
		cin >> concertweight[i];
	}
	
	//dijkstra
	priority_queue<ii,vector<ii>, greater<ii>> setds;
	ll dist[maxn];
	for (int i = 1; i <= n; i++) {
		dist[i] = concertweight[i];
		setds.push(make_pair(dist[i],i));
	}
	while (!setds.empty()) {
		pair<ll,int> tmp = setds.top();
		setds.pop();
		int u = tmp.second;
		for (Edge e: adjacents[u]) {
			int v = e.other;
			ll weight = e.weight;
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				setds.push(make_pair(dist[v],v));
			}
		}
	}
	
	//output
	for (int i = 1; i <= n; i++) {
		cout << dist[i];
		if (i != n) {
			cout << ' ';
		}
	}
	cout << '\n';
		
	return 0;
}