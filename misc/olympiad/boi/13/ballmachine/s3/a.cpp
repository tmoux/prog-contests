#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, Q;
vector<int> adj[maxn];

int minsub[maxn];
int ord[maxn], inv[maxn]; //node to seg, seg to node
int pt = 1;

void prep(int i) {
    minsub[i] = i;
    for (int j: adj[i]) {
        minsub[i] = min(minsub[i],minsub[j]);
    }
    sort(adj[i].begin(),adj[i].end(),[](int a, int b) {
            return minsub[a] < minsub[b];
            });
}
void dfs(int i) {
    for (int j: adj[i]) {
        dfs(j);
    }
    ord[i] = pt;
    inv[pt] = i;
    pt++;
    //cout << i << ' ';
}

const int maxk = 18;
int par[maxk][maxn];

int seg[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    int rt = -1;
    for (int i = 1; i <= N; i++) {
        int pi; cin >> pi;
        if (pi == 0) rt = i;
        else adj[pi].push_back(i);
        par[0][i] = pi;
    }
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= N; i++) {
            par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    prep(rt);
    dfs(rt);
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int k; cin >> k;
            for (int i = 1; i <= k; i++) {
                seg[inv[i]] = 1;
            }
            cout << inv[k] << '\n';
        }
        else {
            int v; cin >> v;
            int res = 0;
            for (int k = maxk - 1; k >= 0; k--) {
                if (par[k][v] == 0) continue;
                int nxt = par[k][v];
                if (seg[nxt] == 1) {
                    res += (1<<k);
                    v = nxt;
                }
            }
            seg[v] = 0;
            cout << res << '\n';
        }
    }
}

