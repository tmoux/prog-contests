#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 205;
int N;
string s;
int a[maxn];
ll dp[maxn][maxn][maxn];

ll f(int se, int en, int pfx) {
    if (se >= en) return 0;
    if (se + 1 == en) return a[pfx];
    ll& res = dp[se][en][pfx];
    if (res != -1) return res;
    res = a[pfx] + f(se+1,en,1);
    for (int i = se + 1; i < en; i++) {
        if (s[i] == s[se]) {
            res = max(res,f(se+1,i,1) + f(i,en,pfx+1));
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    cin >> N >> s;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    ll ans = f(0,N,1);
    cout << ans << '\n';

    return 0;
}

