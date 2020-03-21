#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, a[maxn];

pair<int,pair<int,int>> dp[maxn][maxn];

pair<int,pair<int,int>> f(int l, int r) {
    if (dp[l][r].first != 0) return dp[l][r];
    if (l == r) return dp[l][r] = {1,{a[l],a[r]}};
    if (l == r-1 && a[l] == a[r]) return dp[l][r] = {1,{a[l]+1,a[r]+1}};
    dp[l][r] = {r-l+1,{a[l],a[r]}};
    for (int i = l; i < r; i++) {
        auto m1 = f(l,i);
        auto m2 = f(i+1,r);
        int nl = m1.second.first;
        int nr = m2.second.second;
        int sz = m1.first+m2.first;
        if (m1.second.second == m2.second.first) {
            sz--;
            if (m1.first == 1) {
                nl = m1.second.second+1;
            }
            if (m2.first == 1) {
                nr = m1.second.second+1;
            }
        }
        if (sz < dp[l][r].first) {
            dp[l][r] = {sz,{nl,nr}};
        }
    }
    return dp[l][r];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto ans = f(1,n);
    cout << ans.first << endl;
    //printf("%d: (%d, %d)\n",ans.first,ans.second.first,ans.second.second);
}
