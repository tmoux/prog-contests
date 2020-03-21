#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
int a[maxn];
vector<int> adj[maxn];

ll sum[maxn], mx[maxn];
void dfs(int i, int p) {
    sum[i] = mx[i] = a[i];
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        sum[i] += sum[j];
        mx[i] = max(mx[i],mx[j]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    while (q--) {
        int t, r, k; cin >> t >> r >> k;
        dfs(r,r);
        vector<ll> v;
        for (int i = 1; i <= n; i++) {
            v.push_back(t==1?sum[i]:mx[i]);
        }
        sort(v.begin(),v.end(),greater<ll>());
        cout << v[k-1] << '\n';
    }
}
