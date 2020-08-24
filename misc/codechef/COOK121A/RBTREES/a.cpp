#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int color[maxn];
int cnt[2];
int depth[maxn];
bool bad[maxn];
void dfs(int i, int p, int d) {
    depth[i] = d;
    cnt[d%2]++;    
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i,d+1);
    }
}
ll ans = 0;

vector<int> dfs2(int i, int p) {
    vector<int> v(2,0);
    if (bad[i]) {
        ans += depth[i];
        v[color[i]]++;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        auto nj = dfs2(j,i);
        v[0] += nj[0];
        v[1] += nj[1];
    }
    int mn = min(v[0],v[1]);
    v[0] -= mn;
    v[1] -= mn;
    ans -= 2LL*mn*depth[i];
    return v;
}

void solve() {
    cin >> n;
    cnt[0] = cnt[1] = 0;
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    string s; cin >> s;
    int c0 = 0, c1 = 0;
    for (int i = 1; i <= n; i++) {
        color[i] = s[i-1] == '1' ? 1 : 0;
        if (s[i-1] == '1') {
            c1++;
        }
        else {
            c0++;
        }
    }
    dfs(1,1,0);
    int is = 0;
    if (c0 == cnt[0] && c1 == cnt[1]) {

    }
    else if (c0 == cnt[1] && c1 == cnt[0]) {
        is = 1;
    }
    else {
        cout << -1 << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (((depth[i]%2)^is) != color[i]) {
            bad[i] = true;
        }
        else {
            bad[i] = false;
        }
    }
    ans = 0;
    dfs2(1,1);
    ll curans = ans;
    if (c0 == c1) {
        is = !is;
        for (int i = 1; i <= n; i++) {
            if (((depth[i]%2)^is) != color[i]) {
                bad[i] = true;
            }
            else {
                bad[i] = false;
            }
        }
        ans = 0;
        dfs2(1,1);
        curans = min(curans,ans);
    }
    cout << curans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
