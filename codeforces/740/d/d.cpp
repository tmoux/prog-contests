#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];
struct Edge
{
    int to, wt;
};

vector<Edge> adj[maxn];
int par[20][maxn];
ll depth[maxn];

void dfs(int i, ll d) {
    depth[i] = d;
    for (Edge e: adj[i]) {
        dfs(e.to,d+e.wt);
    }
}

int ans[maxn];

void dfs2(int i) {
    for (Edge e: adj[i]) {
        dfs2(e.to);
        ans[i] += ans[e.to];
    }
    //cout << i << ": " << ans[i] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n-1; i++) {
        int pi, wi; cin >> pi >> wi;
        adj[pi].push_back({i+1,wi});
        par[0][i+1] = pi;
    }
    for (int k = 1; k < 20; k++) {
        for (int i = 1; i <= n; i++) {
            par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    dfs(1,0);
    for (int i = 1; i <= n; i++) {
        ll target = depth[i] - a[i];
        int j = i;
        for (int k = 19; k >= 0; k--) {
            int nj = par[k][j];
            if (nj == 0) continue;
            if (depth[nj] >= target) {
                j = nj;
            }
        }
        j = par[0][j];
        /*
        cout << target << '\n';
        cout << i << ": " << j << '\n';
        */
        ans[par[0][i]]++;
        ans[j]--;
    }
    dfs2(1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

