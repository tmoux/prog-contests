#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, a[maxn];

pair<int,pair<int,int>> dp[maxn][maxn];

pair<int,pair<int,int>> f(int l, int r) {
    if (dp[l][r].first > 0) return dp[l][r];
    if (l == r) return dp[l][r] = {1,{a[l],a[r]}};
    dp[l][r] = {maxn,{-1,-1}};
    for (int i = l; i < r; i++) {
        auto ll = f(l,i), rr = f(i+1,r);
        int nl = ll.second.first;
        int nr = rr.second.second;
        int len = ll.first+rr.first;
        if (ll.second.second == rr.second.first) {
            --len;
            if (ll.first == 1) {
                nl = ll.second.second+1;
            }
            if (rr.first == 1) {
                nr = rr.second.first+1;
            }
        }
        if (len < dp[l][r].first) {
            dp[l][r] = {len,{nl,nr}};
        }
    }
    return dp[l][r];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto ans = f(0,n-1);
    cout << ans.first << endl;
}
