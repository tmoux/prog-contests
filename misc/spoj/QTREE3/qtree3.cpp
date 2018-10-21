#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005, INF = 1e9+7;
int n, q, preorder[maxn], postorder[maxn], sub_size[maxn], real_to_hld[maxn];
int pre = 0, hld_id = 1;
vector<int> adj[maxn];
set<int> blacks[maxn]; //stores blacks in this chain (hld indices)
struct Node {
	int real, parent, lastPrev, _preorder, _postorder;
} nodes[maxn];

int dfs_prep(int i, int par) {
	preorder[i] = pre++;
	sub_size[i] = 1;
	for (int j: adj[i]) {
		if (j == par) continue;
		sub_size[i] += dfs_prep(j,i);
	}
	postorder[i] = pre;
	return sub_size[i];
}

void hld(int i, int par, bool newChain) {
	real_to_hld[i] = hld_id++;
	
	int id = real_to_hld[i];
	nodes[id]._preorder = preorder[i];
	nodes[id]._postorder = postorder[i];
	nodes[id].real = i;
	if (newChain) {
		nodes[id].parent = id;
		nodes[id].lastPrev = real_to_hld[par]; //lastprev[1] = 1
	}
	else {
		nodes[id].parent = nodes[real_to_hld[par]].parent;
		nodes[id].lastPrev = nodes[real_to_hld[par]].lastPrev;
	}
	for (int j: adj[i]) {
		if (j == par) continue;
		if (sub_size[j] * 2 >= sub_size[i]) hld(j,i,false);
	}
	for (int j: adj[i]) {
		if (j == par) continue;
		if (sub_size[j] * 2 < sub_size[i]) hld(j,i,true);
	}
}

int query(int v) {
    int curr = INF;
    set<int>& s = blacks[nodes[v].parent];
    if (!s.empty()) {
        curr = *s.begin();
    }

    if (nodes[v].lastPrev != nodes[v].parent) {
        int nx = query(nodes[v].lastPrev);
        if (nx != INF) curr = nx;
    }
    return curr;
}

int main()
{    
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> q;
	for (int i = 1; i <= n - 1; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs_prep(1,1);
	hld(1,1,true);
    while (q--) {
        int t, v; cin >> t >> v;
        if (t == 0) {
            v = real_to_hld[v];
            set<int>& s = blacks[nodes[v].parent]; 
            if (s.count(v)) s.erase(v);
            else s.insert(v);
        }
        else {
            v = real_to_hld[v];
            int ans = query(v);
            cout << (ans == INF ? -1 : nodes[ans].real) << '\n';
        }
    }

    return 0;
}
