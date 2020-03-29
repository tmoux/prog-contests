#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m, k;
vector<int> adj[maxn];
int C[maxn];

int p[maxn];
int deg[maxn];
int dist[maxn];
int par[maxn];

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        cin >> C[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for (int i = 0; i < n; i++) {
        p[i+1] = C[i+1];
        deg[i+1] = 0;
        dist[i+1] = 0;
        par[i+1] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j: adj[i]) {
            if (p[i] < p[j]) {
                ++deg[j];
            }
        }
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int i = q.front(); q.pop();
        //cout << "processing " << i << endl;
        dist[i] = 1;
        for (int j: adj[i]) {
            if (p[i] > p[j] && dist[j]+1 > dist[i]) {
                dist[i] = dist[j]+1;
                par[i] = j;
            }
            else if (p[i] < p[j]) {
                if (--deg[j] == 0) {
                    q.push(j);
                }
            }
        }
    }
    pair<int,int> x = {-1,-1};
    for (int i = 1; i <= n; i++) {
        x = max(x,{dist[i],i});
    }
    assert(x.first != -1);
    if (x.first <= k) {
        /*
        cout << "priority:\n";
        for (int i = 1; i <= n; i++) {
            cout << i << ": " << ord[i] << endl;
        }
        */
        cout << x.first << ' ';
        for (int i = 1; i <= n; i++) {
            cout << dist[i] << ' ';
        }
        cout << '\n';
        int cur = x.second;
        while (cur != 0) {
            cout << cur << ' ';
            cur = par[cur];
        }
        cout << '\n';
        return;
    }
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
