#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll,pair<ll,ll>> gcd(ll a, ll b) {
    if (a == 0) return {b,{0,1}};
    if (b == 0) return {a,{1,0}};
    ll x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    while (a && b) {
        ll r = a/b;
        ll tmp = b;
        b = a - r * b;
        a = tmp;
        ll tmpx = x2, tmpy = y2;
        x2 = x1 - r * x2;
        y2 = y1 - r * y2;
        x1 = tmpx, y1 = tmpy;
    }
    return {a,{x1,y1}};
}

pair<ll,ll> getPositive(pair<ll,ll> p, ll k1, ll k2) {
    ll a = p.first;
    ll b = p.second;
    //cout << a << ' ' << b << '\n';
    if (a >= 0 && b >= 0) return p;
    if (a < 0) {
        ll k = abs(a/b);
        while (a+k*k2 < 0) k++;
        a += k*k2;
        b -= k*k1;
        return {a,b};
    }
    else {
        assert(b<0);
        ll k = abs(b/a);
        while (b+k*k1 < 0) k++;
        a -= k*k2;
        b += k*k1;
        return {a,b};
    }
}

int main()
{
    ll n; cin >> n;
    ll c = n;
    vector<ll> primes;
    for (ll i = 2; i*i <= n; i++) {
        if (c % i == 0) {
            primes.push_back(i);
            while (c % i == 0) c /= i;
        }
    }
    if (c != 1 && c != n) primes.push_back(c);
    /*
    cout << "Size = " << primes.size() << '\n';
    for (ll i: primes) {
        cout << i << ' ';
    }
    */
    if (primes.size() <= 1) {
        cout << "NO" << '\n';
        return 0;
    }
    sort(primes.begin(),primes.end(),greater<ll>());
    auto g = gcd(primes[0],primes[1]);
    //printf("%d * %d + %d * %d = %d\n",primes[0],g.second.first,primes[1],g.second.second,1);
    auto p = getPositive({g.second.first*(n-1),g.second.second*(n-1)},primes[0],primes[1]);
    printf("%d * %d + %d * %d = %d\n",primes[0],p.first,primes[1],p.second,n-1);
    

    return 0;
}

