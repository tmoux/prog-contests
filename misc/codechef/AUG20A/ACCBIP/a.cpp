#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
const ll INF = 1e18;
int N, C, K;
int a[maxn], b[maxn], c[maxn];
int V[maxn];
int cnt[maxn];

ll dp[maxn][maxn];
ll ch3(int x) {
    if (x < 2) return 0LL;
    return 1LL*x*(x-1)*(x-2)/6;
}
ll ch2(int x) {
    if (x < 1) return 0LL;
    return 1LL*x*(x-1)/2;
}
ll tri[maxn][maxn];

ll g(vector<int>& v) {
    int n = 0;
    for (int i: v) n += i;
    ll tot = ch3(n);
    ll sub = 0;
    for (int i: v) sub += ch3(i);
    for (int i: v) sub += (n-i)*ch2(i);
    tot -= sub;
    return tot;
}

ll f(int i, int k) {
    if (i > C) return 0;
    ll& res = dp[i][k];
    if (res != -1) return res;
    res = INF;
    for (int j = 0; j <= cnt[i] && k-j*V[i] >= 0; j++) {
        res = min(res,f(i+1,k-j*V[i])+tri[i][j]);
    }
    return res;
}

void solve() {
    memset(cnt,0,sizeof cnt);
    memset(tri,0,sizeof tri);
    cin >> N >> C >> K;
    vector<map<int,int>> mps(C+1);
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i] >> c[i];
        cnt[c[i]]++;
        mps[c[i]][a[i]]++;
    }
    for (int i = 1; i <= C; i++) {
        vector<int> v;
        for (auto p: mps[i]) v.push_back(p.second);
        sort(v.begin(),v.end());
        int idx = 0;
        int pt = 0;
        while (idx < v.size()) {
            tri[i][pt++] = g(v);
            if (--v[idx] == 0) idx++;
        }
    }
    for (int i = 1; i <= C; i++) cin >> V[i];
    memset(dp,-1,sizeof dp);
    ll ans = f(1,K);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    while (true) {
        int n; cin >> n;
        map<int,int> mp;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            ++mp[ai];
        }
        vector<int> v;
        for (auto p: mp) v.push_back(p.second);
        ll tot = ch3(n);
        ll sub = 0;
        for (int i: v) sub += ch3(i);
        for (int i: v) sub += (n-i)*ch2(i);
        tot -= sub;
        cout << " = " << tot << endl;
    }
    return 0;
    */
    int t; cin >> t;
    while (t--) solve();
}
