using namespace std;
#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define pi pair<int, int>
#define maxn 20005
#define mod 998244353
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
ll ksm(ll a, ll b) {if (b == 0) return 1; ll ns = ksm(a, b >> 1); ns = ns * ns % mod; if (b & 1) ns = ns * a % mod; return ns;}
using namespace std;
#define ui unsigned int
int n, c;
ui dp[maxn][maxn], bst[maxn];
vector<pi> eg[maxn];
vi tr;
int fl[maxn];
int fa[maxn];
void dfs1(int a) {
    for (auto v: eg[a]) {
        if (v.fi == fa[a]) continue;
        fa[v.fi] = a;
        fl[v.fi] = lower_bound(tr.begin(), tr.end(), v.se) - tr.begin();
        dfs1(v.fi);
    }
}
const ui inf = 4e9;
void dfs2(int a) {
    for (auto [v, d] : eg[a]) {
        if (v == fa[a]) continue;
        dfs2(v);
    }
    bst[a] = inf;
    ui sbst = 0;
    for (auto [v, d] : eg[a]) {
        if (v == fa[a])
            continue;
        sbst += bst[v];
    }

    for (int i = 0; i < tr.size(); i++) {
        // fa len is i
        if (i < fl[a]) dp[a][i] = inf;
        else {
            dp[a][i] = tr[i] - tr[fl[a]];
            if (a == 1) dp[a][i] = 0;
        }
        // not involving c
        ll cr = 0;
        for (auto [v, d] : eg[a]) {
            if (v == fa[a]) continue;
            cr += dp[v][i];
        }
        if (cr >= inf) cr = inf;
        dp[a][i] += min(sbst + (int)eg[a].size() * c, (ui)cr);
        //cout << a << ' ' << i << ' ' << dp[a][i] << endl;
        chkmin(bst[a], dp[a][i]);
    }
}
int main() {
    cin >> n >> c;
    for (int i = 1; i < n; i++) {
        int u, v, s;
        scanf("%d%d%d", &u, &v, &s);
        tr.pb(s);
        eg[u].pb(mp(v, s));
        eg[v].pb(mp(u, s));
    }
    sort(tr.begin(), tr.end());
    dfs1(1);
    dfs2(1);
    if (n == 1) bst[1] = 0;
    cout << bst[1] << endl;
    return 0;
}
