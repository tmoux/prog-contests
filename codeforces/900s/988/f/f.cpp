#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int a, n, m;
bool isRain[maxn];
ll umbrella[maxn];
vector<pair<int,int>> u[maxn];

ll dp[maxn][maxn];
ll f(int i, int j) { //at position i, with umbrella idx j
    ll& res = dp[i][j];
    if (res != -1) return res;
    if (i == a) return 0;
    int jj = j;
    if (!u[i].empty() && umbrella[u[i][0].second] < umbrella[j]) jj = u[i][0].second;
    if (isRain[i]) {
        //cout << i << ": " << jj << ' ' << umbrella[jj] << endl;
        return res = umbrella[jj] + f(i+1,jj);
    }
    else {
        return res = min(f(i+1,0),
                         umbrella[jj]+f(i+1,jj));
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> n >> m;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        for (int j = l; j < r; j++) {
            isRain[j] = true;
        }
    }
    umbrella[0] = 2e9;
    for (int i = 1; i <= m; i++) {
        int x, p; cin >> x >> p;
        umbrella[i] = p;
        u[x].push_back({p,i});
    }
    for (int i = 0; i <= a; i++) {
        sort(u[i].begin(),u[i].end());
    }
    memset(dp,-1,sizeof dp);
    ll ans = f(0,0);
    cout << (ans >= 1e9 ? -1 : ans) << '\n';
}
