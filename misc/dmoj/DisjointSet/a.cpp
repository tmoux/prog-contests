#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
struct Edge {
	int a, b, weight, id;
	bool operator<(const Edge& r) const {
		return weight < r.weight;
	}
};

int parent[maxn];
int Find(int i) {
	return parent[i] < 0 ? i : parent[i] = Find(parent[i]);
}

bool Union(int u, int v) {
	u = Find(u);
	v = Find(v);
	if (u == v) return false;
	if (parent[u] > parent[v]) swap(u,v);
	parent[u] += parent[v];
	parent[v] = u;
	return true;
}

int N, M;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    memset(parent,-1,sizeof parent);
    vector<Edge> edges;
    for (int i = 0; i < M; i++) {
    	int u, v; cin >> u >> v;
    	Edge e = {u,v,i+1,i+1};
    	edges.emplace_back(e);
    }
    vector<int> ans;
    //cout << Union(1,2) << '\n';
    for (Edge& e: edges) {
    	//cout << e.a << ' ' << e.b << '\n';
    	if (Union(e.a,e.b)) {
    		//cout << e.id << '\n';
    		ans.emplace_back(e.id);
    	}
    }
    if (ans.size() == N - 1) {
    	for (int i: ans) {
    		cout << i << '\n';
    	}
    }
    else cout << "Disconnected Graph\n";

    return 0;
}