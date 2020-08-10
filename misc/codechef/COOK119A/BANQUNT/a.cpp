#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 998244353;
ll mult(ll a, ll b) {
    return (a*b) % MOD;
}
ll modexp(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

ll calc(ll x) {
    if (x&1) return 1;
    return x/2+1;
}

int num(ll x, ll N, ll M) {
    if (x > N) return 0;
    int res = 1;
    ll y = x;
    while (true) {
        ll z = y*M;
        if (z/M != y) {
            //overflow, stop
            break;
        }
        else if (z > N) {
            break;
        }
        else {
            y = z;
            res++;
        }
    }
    return res;
}

ll cnt(ll x, ll M) {
    return (M-1)*(x/M)+(x%M);
}

ll inrange(ll l, ll r, ll M) {
    return cnt(r,M) - cnt(l-1,M);
}

void solve(ll N, ll M) {
    ll ans = 0, ways = 1;
    ll ub = N;
    int cur = 0;
    while (ub >= 1) {
        ll lb = ub/M+1;

        ll numStart = inrange(lb,ub,M);
        cur++;
        /*
        cout << cur << ": " << lb << ' ' << ub << ", count = " << numStart << endl;
        cout << "multiplying " << calc(cur) << "^" << numStart << ": " << modexp(calc(cur),numStart) << '\n';
        */
        ans += numStart*((cur+1)/2);
        ways = mult(ways,modexp(calc(cur),numStart));

        ub = lb-1;
    }
    cout << ans << ' ' << ways << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    //t = 10000;
    while (t--) {
        ll N, M; cin >> N >> M;
        //N = 1e18;
        //M = 2;
        solve(N,M);
    }
}
