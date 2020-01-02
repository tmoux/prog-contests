#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int par[maxn];
int depth[maxn];
int sz[maxn];

void dfs(int i, int p) {
    par[i] = p;
    depth[i] = depth[p] + 1;
    sz[i] = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        sz[i] += sz[j];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    int d = (depth[n]-depth[1]-1)/2;
    int c = n;
    while (d--) {
        c = par[c];
    }
    int a = n-sz[c];
    int b = sz[c];
    if (d&1) {
        //b just moved
        cout << (b >= a ? "Snuke" : "Fennec") << '\n';
    }
    else {
        cout << (a >= b ? "Fennec": "Snuke") << '\n';
    }
}

