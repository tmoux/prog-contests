#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e3+20;
int n;
vector<int> adj[maxn];
int sub_size[maxn], prep[maxn], post[maxn], real_to_hld[maxn], pre, hld_id = 1;

struct Node
{
    int realid, parent, lastPrev, preorder, postorder;
    void debug() {
    }
} nodes[maxn];

int dfs_setup(int i, int par) {
    sub_size[i] = 1;
    prep[i] = pre++;
    for (int j: adj[i]) {
        if (j == par) continue;
        sub_size[i] += dfs_setup(j,i);
    }
    post[i] = pre;
    return sub_size[i];
}

void hld_decomp(int i, int par, bool newChain) { //these are using the real id's
    real_to_hld[i] = hld_id++;
    int id = real_to_hld[i];
    nodes[id].realid = i;
    nodes[id].preorder = prep[i];
    nodes[id].postorder = post[i];
    if (newChain) {
        nodes[id].parent = id;
        nodes[id].lastPrev = real_to_hld[par]; //lastPrev[1] = 1
    }
    else {
        nodes[id].parent = nodes[real_to_hld[par]].parent;
        nodes[id].lastPrev = nodes[real_to_hld[par]].lastPrev;
    }

    for (int j: adj[i]) {
        if (j == par) continue;
        if (sub_size[j] * 2 >= sub_size[i]) hld_decomp(j,i,false);
    }
    for (int j: adj[i]) {
        if (j == par) continue;
        if (sub_size[j] * 2 < sub_size[i]) hld_decomp(j,i,true);
    }
}

bool isAncestor(int u, int v) { //whether u is an ancestor of v, hld terms
    return nodes[u].preorder <= nodes[v].preorder && nodes[v].preorder < nodes[u].postorder;   
}

int lca(int u, int v) { //returns lca(u,v) in terms of hld-id's
    while (!isAncestor(nodes[u].parent,v)) {
        u = nodes[u].lastPrev;
    }
    int lo = nodes[u].parent, hi = u;
    if (isAncestor(hi,v)) return hi;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (isAncestor(mid,v)) {
            lo = mid;
        }
        else hi = mid;
    }
    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            int m; cin >> m;
            while (m--) {
                int ai; cin >> ai;
                adj[i].push_back(ai);
                adj[ai].push_back(i);
            }
        }
        dfs_setup(1,1);
        hld_decomp(1,1,true);
        int q; cin >> q;
        cout << "Case " << a << ":\n"; 
        while (q--) {
            int u, v; cin >> u >> v;
            u = real_to_hld[u], v = real_to_hld[v];
            cout << nodes[lca(u,v)].realid << '\n';
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = real_to_hld[i], v = real_to_hld[j];
            cout << i << ' ' << j << ": " << nodes[lca(u,v)].realid << '\n';
        }
    }
    
    for (int i = 1; i <= n; i++) {
        cout << i << ":\n";
        printf("Real id: %d\nParent: %d\nPrevious: %d\nPreorder: %d\nPostorder : %d\n",nodes[i].realid,nodes[nodes[i].parent].realid,nodes[nodes[i].lastPrev].realid,nodes[i].preorder,nodes[i].postorder);
    }
    */

    return 0;
}
	

