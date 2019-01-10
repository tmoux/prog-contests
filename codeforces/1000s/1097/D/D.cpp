#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int M = 1e9+7;
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}
ll n;
int k;

gp_hash_table<ll,vector<ll>> facs;
ll dp[10005][2000];
ll inv[2000];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }
    vector<ll> factors;
    for (ll i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (i != n/i) factors.push_back(n/i);
            //cout << i << ' ' << n/i << '\n';
        }
    }
    for (int i = 0; i < factors.size(); i++) {
        //cout << i << ": ";
        ll ii = factors[i];
        for (int j = 0; j < factors.size(); j++) {
            ll jj = factors[j];
            if (ii % jj == 0) {
                facs[i].push_back(j);
                //cout << j << ' ';
            }   
        }
        //cout << '\n';
        dp[0][i] = ii;
        inv[i] = modexp(facs[i].size(),M-2);
    }
    

    for (int K = 1; K <= k; K++) {
        for (int i = 0; i < factors.size(); i++) {
            for (int j: facs[i]) {
                dp[K][i] = (dp[K][i] + dp[K-1][j] * inv[i]) % M;
            }
        }
    }
    cout << dp[k][1] << '\n';

    return 0;
}

