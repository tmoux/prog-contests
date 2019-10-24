#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mx = 19;
int digit[mx];
int sz = -1;
ll n;
int m;

ll dp[1<<mx][105];

int e10[mx];

ll f(int mask, int mod) {
    if ((mask+1) == (1<<(sz+1))) return mod==0;
    if (dp[mask][mod] != -1) return dp[mask][mod];
    dp[mask][mod] = 0;
    int count = 0;
    for (int i = 0; i <= sz; i++) {
        if (mask & (1<<i)) count++;
    }
    for (int i = 0; i <= sz; i++) {
        if (mask & (1<<i)) continue;
        if (count == 0 && digit[i] == 0) continue;
        dp[mask][mod] += f(mask|(1<<i),(mod+e10[sz-count]*digit[i])%m);
    }
    return dp[mask][mod];
}

ll fac[20];

int dc[10];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    while (n > 0) {
        digit[++sz] = n % 10;
        dc[n%10]++;
        n /= 10;
    }
    e10[0] = 1;
    for (int i = 1; i <= sz; i++) {
        e10[i] = (e10[i-1]*10) % m;
    }
    memset(dp,-1,sizeof dp);
    ll ans = f(0,0);
    fac[0] = 1;
    for (int i = 1; i <= 18; i++) {
        fac[i] = i*fac[i-1];
    }
    for (int d = 0; d < 10; d++) {
        ans /= fac[dc[d]];
    }
    cout << ans << '\n';
}

