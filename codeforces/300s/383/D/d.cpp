#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005, maxx = 10005, M = 1e9+7;
int n, a[maxn];

void madd(int& a, int b) {
    a = (a+b) % M;
}

int dp[maxn][maxx];

int f(int l, int r) {
    if (l >= r) return 0;
    int mid = (l+r)/2;
    int res = 0;
    madd(res,f(l,mid));
    madd(res,f(mid+1,r));
    for (int i = l; i <= r; i++) {
        for (int j = 0; j < maxx; j++) {
            dp[i][j] = 0;
        }
    }
    dp[l][0] = dp[l][a[l]] = 1;
    for (int i = l+1; i <= r; i++) {
        for (int j = 0; j < maxx; j++) {
            dp[i][j] = dp[i-1][j];
            if (a[i] >= j) madd(dp[i][j],dp[i-1][j-a[i]]);
        }
    }
    return res;        
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = f(1,n);
    cout << ans << '\n';
}

