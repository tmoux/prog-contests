#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
int p[maxn];
int idx[maxn];
vector<int> adj[maxn];
int hap[maxn], mad[maxn];
int sz[maxn];

void dfs(int i, int par) {
    sz[i] = p[i];
    for (int j: adj[i]) if (j != par) {
        dfs(j,i);
        sz[i] += sz[j];
    }
}
bool poss = true;
void dfs2(int i, int par) {
    int nhap = 0, nmad = 0;
    for (int j: adj[i]) if (j != par) {
        dfs2(j,i);
        nhap += hap[j];
        nmad += mad[j];
    }
    if (nhap + nmad == sz[i]-p[i] && nhap <= hap[i]) {

    }
    else {
        poss = false;
        //cout << "BAD " << i << endl;
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        p[i] = 0;
        idx[i] = 0;
        adj[i].clear();
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> idx[i];
    }
    for (int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1,1);
    poss = true;
    for (int i = 1; i <= n; i++) {
        if ((sz[i]-idx[i]) % 2 != 0) {
            poss = false;
        }
        else {
            mad[i] = (sz[i]-idx[i])/2;
            hap[i] = sz[i]-mad[i];
            if (mad[i] < 0 || hap[i] < 0) poss = false;
            //cout << i << ": " << hap[i] << ' ' << mad[i] << '\n';
        }
    }
    dfs2(1,1);
    cout << (poss ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
