#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int deg[maxn];

int make(int i, int p) {
    int cnt = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        cnt++;
    }
    if (cnt == 1) {
        for (int j: adj[i]) {
            if (j == p) continue;
            return 1 + make(j,i);
        }
    }
    return 0;
}

set<int> dd[maxn];

void DFS(int i, int p, int d) {
    dd[d].insert(deg[i]);
    for (int j: adj[i]) {
        if (j == p) continue;
        DFS(j,i,d+1);
    }
}

bool tr(int i) {
    DFS(i,i,0);
    for (int j = 0; j <= n; j++) {
        if (dd[j].size() > 1) {
            return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<int> leafs;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) leafs.push_back(i);
    }
    map<int,vector<int>> dist;
    for (int i: leafs) {
        dist[make(i,i)].push_back(i);
        //cout << i << ": " << dist[i] << '\n';
    }
    if (dist.size() == 1) {
        if (tr(dist.begin()->second[0])) {
            cout << dist.begin()->second[0] << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }
    else if (dist.size() == 2) {
        int mnocc = maxn;
        int idx = -1;
        for (auto& p: dist) {
            if (p.second.size() < mnocc) {
                mnocc = p.second.size();
                idx = p.second[0];
            }
        }
        if (mnocc > 1) {
            cout << -1 << '\n';
        }
        else {
            if (tr(idx)) {
                cout << idx << '\n';
            }
            else {
                cout << -1 << '\n';
            }
        }
    }
    else {
        cout << -1 << '\n';
        return 0;
    }
}

