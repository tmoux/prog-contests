#include <bits/stdc++.h>
using namespace std;
int n;
struct Edge
{
	int to, id;
	Edge(int a, int b) {
		to = a;
		id = b;
	}
};
int pre[100000];
int low[100000];
bool v[100000];

int point = 0;
vector<Edge> adj[100000];


void go(int now, int fromID) {
	pre[now] = point++;
	v[now] = true;
	low[now] = pre[now];
	bool isArt = false;
	int childCnt = 0;
	for (int i = 0; i < adj[now].size(); i++) {
		if (adj[now][i].id == fromID) continue;
		int to = adj[now][i].to;
		if (v[to]) {
			//to must be an ancestor of now
			low[now] = min(low[now],pre[to]);
		}
		else {
			//bold edge going downwards
			go(to,adj[now][i].id);
			childCnt++;
			low[now] = min(low[now],low[to]);
			if (low[to] >= pre[now]) {
				isArt = true;
			}
			if (pre[now] < low[to]) {
				cout << "Bridge: " << now << " -> " << to << '\n';
			}
		}
	}
	if (fromID == -1) {
		isArt = childCnt != 1;
	}
	if (isArt) {
		cout << "Is articulation point " << now << '\n';
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		v[i] = false;
	}
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back({b,i});
		adj[b].push_back({a,i});
	}
	go(0,-1);
	return 0;
}