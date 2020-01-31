#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n;
vector<int> adj[maxn];
int c[maxn];
int sz[maxn];

void dfs(int i) {
    sz[i] = 1;
    for (int j: adj[i]) {
        dfs(j);
        sz[i] += sz[j];
    }
}

vector<pair<int,int>> v[maxn];
int ans[maxn];

void dfs2(int i) {
    for (int j: adj[i]) {
        dfs2(j);
        for (auto k: v[j]) {
            v[i].push_back(k);
        }
    }
    sort(v[i].begin(),v[i].end());
    for (int j = 0; j < v[i].size(); j++) {
        v[i][j].first = j+1;
    }
    if (c[i] == v[i].size()) {
        v[i].push_back({c[i]+1,i});
    }
    else {
        v[i].insert(v[i].begin()+c[i],{c[i]+1,i});
        for (int j = c[i]+1; j < v[i].size(); j++) {
            v[i][j].first++;
        }
    }
    /*
    cout << i << "\n";
    for (auto p: v[i]) {
        cout << p.first << ' ' << p.second << '\n';
    }
    */
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int root = -1;
    for (int i = 1; i <= n; i++) {
        int pi, ci; cin >> pi >> ci;
        c[i] = ci;
        if (pi != 0) {
            adj[pi].push_back(i);
        }
        else root = i;
    }
    dfs(root);
    for (int i = 1; i <= n; i++) {
        if (c[i] >= sz[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    dfs2(root);
    for (auto p: v[root]) {
        ans[p.second] = p.first;
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

