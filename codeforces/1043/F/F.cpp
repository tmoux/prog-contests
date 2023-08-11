#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll modexp(ll x, ll n, int M) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2,M);
    return (x*modexp((x*x)%M,n/2,M))%M;
}

const int maxn = 3e5+5, M = 1e9+7;
int n, a[maxn], cnt[maxn], mobius[maxn]; 
ll fac[maxn], inv[maxn];

ll comb(int n, int k) {
    if (n < k) return 0;
    return (((fac[n] * inv[k]) % M) * inv[n-k]) % M;
}

int check(int k) {
    int res = 0;
    for (int x = 1; x < maxn; x++) {
        res = (res + (mobius[x] * comb(cnt[x],k) + M) % M) % M;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int gc = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;            
        gc = __gcd(gc,a[i]);
    }
    if (gc > 1) {
        cout << -1 << '\n';
        return 0;
        //now assume one subset will work
    }
    //mobius sieve
    mobius[1] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 2*i; j < maxn; j += i) {
            cnt[i] += cnt[j];
            mobius[j] -= mobius[i];
        }
    }
    //build factorial tables
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = (fac[i-1] * i) % M;   
    }
    for (int i = 0; i < maxn; i++) {
        inv[i] = modexp(fac[i],M-2,M);
    }
    //now binary search
    int lo = 0, hi = n;
    while (lo + 1 < hi) {
        int m = (lo+hi)>>1;
        ll c = check(m);
        (c == 0 ? lo : hi) = m;    
    }
    cout << hi << '\n';
    /*
    for (int i = 1; i <= 10; i++) {
        cout << i << ": " << check(i) << '\n';
    }
    */
    

    return 0;
}

