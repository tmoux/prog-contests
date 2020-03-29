#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 250005, maxk = 18;
int n, a[maxn];
vector<int> lis[maxn];
int depth[maxn];

int par[maxk][maxn];

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk-1; k >= 0; k--) {
        int bb = par[k][b];
        if (depth[bb] >= depth[a]) {
            b = bb;
        }
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

int ans[maxn];

void solve() {
    memset(depth,0,sizeof depth);
    for (int i = 0; i <= n; i++) {
        lis[i].clear();
    }
    memset(par,0,sizeof par);
    lis[0].push_back(0);
    for (int i = 1; i <= n; i++) {
        int lo = 0, hi = n+3;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            if (!lis[mid].empty() && lis[mid].back() < a[i]) {
                lo = mid;
            }
            else hi = mid;
        }
        //cout << i << ' ' << lo+1 << '\n';
        lis[lo+1].push_back(a[i]);
        hi = lis[lo].back();
        int l = lis[lo].size()-1;
        for (int k = maxk-1; k >= 0; k--) {
            int nl = (l-(1<<k));
            if (nl >= 0 && lis[lo][nl] < a[i]) {
                l = nl;
            }
        }
        l = lis[lo][l];

        int lc = lca(l,hi);
        par[0][a[i]] = lc;
        for (int k = 1; k < maxk; k++) {
            par[k][a[i]] = par[k-1][par[k-1][a[i]]];
        }
        depth[a[i]] = depth[lc] + 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    solve();
    for (int i = 1; i <= n; i++) {
        ans[i] += depth[a[i]]-1;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = n+1-a[i];
    }
    reverse(a+1,a+1+n);
    solve();
    for (int i = 1; i <= n; i++) {
        ans[n+1-i] += depth[a[i]]-1;
    }
    //output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
