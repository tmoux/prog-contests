#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, m; cin >> n >> m;
    vector<ll> A(n+1), B(m+1);
    for (ll i = 1; i <= n; i++) {
        cin >> A[i];
        A[i] += A[i-1];
    }
    for (ll i = 1; i <= m; i++) {
        cin >> B[i];
        B[i] += B[i-1];
    }
    ll x; cin >> x;
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = i; j <= n; j++) {
            for (ll k = 1; k <= m; k++) {
                for (ll l = k; l <= m; l++) {
                    ll a = j-i+1;
                    ll b = l-k+1;
                    ll f = (A[j]-A[i-1])*(B[l]-B[k-1]);
                    if (f <= x) {
                        ans = max(ans,a*b);
                    }
                }
            }
        }
    }
    cout << ans << '\n';


    return 0;
}

