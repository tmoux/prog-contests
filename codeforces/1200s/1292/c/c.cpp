#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//assign edges weights 0..n-2 to maximize the sum
//of the mex of the path for every path between each pair of vertices
const int maxn = 3005, maxk = 12;
int n;
vector<int> adj[maxn];
int depth[maxn];
int par[maxk][maxn];
ll sz[maxn];
void root(int i, int p) {
    depth[i] = depth[p] + 1;    
    par[0][i] = p;
    sz[i] = 1;
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        root(j,i);
        sz[i] += sz[j];
    }
}
int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk-1; k >= 0; k--) {
        int bb = par[k][b];
        if (depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
        int aa = par[k][a], bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

ll dp[maxn][maxn];

int anc(int i, int lc) {
    for (int k = maxk-1; k >= 0; k--) {
        if (depth[par[k][i]] > depth[lc]) i = par[k][i];
    }
    return i;
}

ll f(int i, int j) {
    ll& res = dp[i][j];
    if (res != -1) return res;
    if (i == par[0][j]) {
        res = sz[j]*(n-sz[j]);
    }
    else if (j == par[0][i]) {
        res = sz[i]*(n-sz[i]);
    }
    else {
        assert(i != j);
        int lc = lca(i,j);
        if (lc == i) {
            int an = anc(j,lc);    
            //cout << i << ' ' << j << ' ' << an << '\n';
            res = (n-sz[an])*sz[j]; 
            res += max(f(an,j),f(i,par[0][j]));
        }
        else if (lc == j) {
            int an = anc(i,lc);
            res = (n-sz[an])*sz[i];
            res += max(f(i,an),f(par[0][i],j));
        }
        else {
            res = sz[i]*sz[j];
            res += max(f(par[0][i],j),f(i,par[0][j]));
        }
    }
    //printf("[%d][%d]: %d\n",i,j,res);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    root(1,0);
    ll ans = 0;
    memset(dp,-1,sizeof dp);
    //f(4,5);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            ans = max(ans,f(i,j));
        }
    }
    cout << ans << '\n';
}
