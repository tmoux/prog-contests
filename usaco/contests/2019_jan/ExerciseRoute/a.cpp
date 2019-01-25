#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, maxk = 18;
int N, M;
vector<int> adj[maxn];
int cnt[maxn];
int par[maxk][maxn];
int depth[maxn];

void dfs(int i, int p) {
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk - 1; k >= 0; k--) {
        int bb = par[k][0];
        if (bb != 0 && depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk - 1; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

int main()
{
    freopen("exercise.in","r",stdin); freopen("exercise.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int r = rand() % N + 1;
    dfs(r,r);
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= N; i++) {
            par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    M -= N - 1;
    vector<pair<int,int>> vs;
    while (M--) {
        int a, b; cin >> a >> b;
        vs.push_back({a,b});
        cnt[a]++;
        cnt[b]++;
    }
    ll ans = 0;
    for (auto p: vs) {
        int a = p.first;
        int b = p.second;
        if (depth[a] > depth[b]) swap(a,b);
        int lc = lca(a,b);
        ll r = 0;
        while (true) {
            r += cnt[b];    
            if (b == lc) break;
            b = par[0][b];
        }
        while (true) {
            if (a == lc) break;
            r += cnt[a];
            a = par[0][a];
        }
        r -= 2;
        ans += r;
    }
    ans /= 2;
    cout << ans << '\n';

    return 0;
}

