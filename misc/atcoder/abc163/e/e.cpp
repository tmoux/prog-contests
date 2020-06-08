#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n, a[maxn];
int p[maxn];
vector<pair<int,int>> v(n);
ll dp[maxn][maxn];

ll f(int l, int r) {
    ll& res = dp[l][r];
    if (res != -1) return res;
    if (l > r) return res = 0;
    int i = l + (n-1-r);
    ll val = v[i].first;
    int pos = v[i].second;
    res = max(val*abs(pos-l)+f(l+1,r),
              val*abs(pos-r)+f(l,r-1));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        v.push_back({a[i],i});
    }
    sort(v.begin(),v.end(),greater<pair<int,int>>());
    memset(dp,-1,sizeof dp);
    cout << f(0,n-1) << '\n';
}
