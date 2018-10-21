#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, sub_size[maxn];
struct Edge { int to, color; };
vector<Edge> adj[maxn];
bool blocked[maxn];

int dfs_size(int i, int p) {
	sub_size[i] = 1;
	for (Edge& e: adj[i]) {
		if (blocked[e.to] || e.to == p) continue;
		sub_size[i] += dfs_size(e.to,i);
	}
	return sub_size[i];
}

int getCentroid(int i, int p, int compSize) {
	for (Edge& e: adj[i]) {
		if (blocked[e.to] || e.to == p) continue;
		if (sub_size[e.to]*2 > compSize) 
			return getCentroid(e.to,i,compSize);
	}
	return i;
}

inline int gt(map<int,int>& mp, int i) {
	return (mp.count(i) ? mp[i] : 0);
}

int seen[2*maxn+50], offset = 100020;
void getPaths(int i, int p, map<int,int>& a, map<int,int>& b, int curr) {
	if (seen[curr+offset] > 0) a[curr]++;
	else b[curr]++;
	seen[curr+offset]++;
	for (Edge& e: adj[i]) {
		if (e.to == p || blocked[e.to]) continue;
		getPaths(e.to,i,a,b,curr+e.color);
	}
	seen[curr+offset]--;
}

ll solveTree(int centroid) {
	map<int,int> hasRest, noRest;
	noRest[0]++;
	ll res = 0;
	for (Edge& e: adj[centroid]) {
		if (blocked[e.to]) continue;
		map<int,int> addRest, addnoRest;
		getPaths(e.to,centroid,addRest,addnoRest,e.color);
		for (auto& p: addRest) {
			res += 1LL*(gt(hasRest,-p.first) + gt(noRest,-p.first)) * p.second;
		}
		for (auto& p: addnoRest) {
			if (p.first != 0) res += 1LL*(gt(hasRest,-p.first)) * p.second;
			else {
				res += 1LL*(gt(hasRest,-p.first) + gt(noRest,-p.first) - 1)*p.second;
			}
		}
		for (auto& p: addRest) {
			hasRest[p.first] += p.second;
		}
		for (auto& p: addnoRest) {
			noRest[p.first] += p.second;
		}
	}
	return res;
}

ll decomp(int i) {
	int compSize = dfs_size(i,i);
	int centroid = getCentroid(i,i,compSize);
	ll res = solveTree(centroid);
	blocked[centroid] = true;
	for (Edge& e: adj[centroid]) {
		if (blocked[e.to]) continue;
		res += decomp(e.to);
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("yinyang.in","r",stdin);
    freopen("yinyang.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
    	int a, b, t; cin >> a >> b >> t;
    	t = t == 0 ? -1 : 1;
    	adj[a].push_back({b,t});
    	adj[b].push_back({a,t});
    }
    cout << decomp(1) << '\n';
    return 0;
}