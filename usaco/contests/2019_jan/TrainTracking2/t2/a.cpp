#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
int MX = 5;
int N, K, mn[maxn];

ll madd(ll a, ll b) {
    return a = (a+b)%M;
}

ll msub(ll a, ll b) {
    return (a-b+M)%M;
}

ll mult(ll a, ll b) {
    return a = (1LL*a*b)%M;
}

ll modpow(ll b, ll n) {
    ll res = 1;
    while (n) {
        if (n&1) res = mult(res,b);
        b = mult(b,b);
        n >>= 1;
    }
    return res;
}

ll solve(int mval, int len) {
    ll x = MX-mval;
    ll xTok = modpow(x,K);
    vector<ll> dp(len+2);
    dp[0] = 1;
    for (int i = 1; i <= len+1; i++) {
        dp[i] = mult(x,dp[i-1]);
        if (i-K-1 >= 0) dp[i] = msub(dp[i],mult(modpow(x+1,K),dp[i-K-1]));
        dp[i] = madd(dp[i],dp[i-1]);
    }
    /*
    for (int i = 1; i <= min(K+1,len+1); i++) {
        dp[i] = modpow(x+1,i-1);
    }
    for (int i = K+1; i <= len + 1; i++) {
        dp[i] = dp[i-1];
        dp[i] = msub(dp[i],mult(dp[i-K-1],modpow(x,K-1)));
        dp[i] = mult(dp[i],x);
        dp[i] = madd(dp[i],dp[i-1]);
    }
    */
    for (int i = 1; i <= len + 1; i++) {
        cout << i << ": " << dp[i] << '\n';
    }
    return dp[len+1];
}

int main()
{
    //freopen("tracking2.in","r",stdin); freopen("tracking2.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N-K+1; i++) cin >> mn[i];
    vector<pair<int,int>> pairs;
    int curr = -1;
    int cnt = 0;
    for (int i = 1; i <= N-K+1; i++) {
        if (curr == mn[i]) cnt++;
        else {
            if (cnt > 0) {
                pairs.push_back({curr,cnt});
            }
            curr = mn[i];
            cnt = 1;
        }
    }
    pairs.push_back({curr,cnt});
    if (pairs.size() == 1) {
        //all the same
        ll ans = solve(pairs[0].first,N);
        cout << ans << '\n';
    }
    else {
        ll res = 1;
        for (int i = 0; i < pairs.size(); i++) {
            int mval = pairs[i].first;
            int s = pairs[i].second;
            int len = -1;
            if (i == 0) {
                if (mval < pairs[1].first) len = s - 1;
                else len = s + K - 1;
            }
            else if (i == pairs.size() - 1) {
                if (mval < pairs[i-1].first) len = s - 1;
                else len = s + K - 1;
            }
            else {
                if (pairs[i-1].first > mval) {
                    if (pairs[i+1].first > mval) len = max(0,s-K-1);
                    else len = s - 1;
                }
                else {
                    if (pairs[i+1].first > mval) len = s - 1;
                    else len = s + K - 1;
                }
            }
            assert(len != -1);
            res = mult(res,solve(mval,len));
        }
        cout << res << '\n';
    }

    return 0;
}

