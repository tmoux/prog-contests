#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

const int M = 998244353;

ll ex(ll x, int n) {
    if (n == 1) return x;
    return x*ex(x,n-1);
}

ll isPow(ll x, int n) {
    double f = 1.0/(double)(n);
    ll r = (ll)(pow(x,f));
    for (ll rr = r <= 5 ? 1 : r-5; rr <= r + 5; rr++) {
        if (ex(rr,n) == (x)) return rr;
    }
    return 0;
}

ll gcd(ll a, ll b) {
    if (a == 0 || b == 0) return a + b;
    return gcd(b,a%b);
}

ll mult(ll r, ll x) {
    return (r*x) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    map<ll,int> primes;
    int n; cin >> n;
    vector<ll> A(n);
    vector<bool> vis(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) {
        for (int j = 4; j >= 2; j--) {
            ll p = isPow(A[i],j);
            if (p != 0) {
                vis[i] = true;
                primes[p] += j;
                break;
            }
        }
    }
    map<ll,int> special;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll gc = __gcd(A[i],A[j]);
            if (A[i] == A[j]) continue;
            if (gc == 1) continue;
           
            if (!vis[i]) {
                primes[gc]++;
                if (A[i] > gc) primes[A[i]/gc]++;
                vis[i] = true;
            }
            if (!vis[j]) {
                primes[gc]++;
                if (A[j] > gc) primes[A[j]/gc]++;
                vis[j] = true;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A[i] == A[j] && !vis[i] && !vis[j]) {
                special[A[i]]++;
                vis[i] = true;
                special[A[i]]++;
                vis[j] = true;
            }
        }
    }
                
    ll res = 1;
    for (auto p: special) {
        res = mult(res,p.second+1);
        res = mult(res,p.second+1);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            res = mult(res,2);
            res = mult(res,2);
        }
    }
    //cout << res << '\n';
    for (auto& p: primes) {
        //cout << p.first << ": " << p.second << '\n';
        res = mult(res,p.second+1);
    }
    cout << res << '\n';

    return 0;
}

