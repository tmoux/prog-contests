#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll D;
int q;

map<ll,int> primes;
vector<pair<ll,int>> v;

void factor(ll x) {
    for (ll i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
                primes[i]++;
            }
            factor(x);
            return;
        }
    }
    if (x > 1) primes[x]++;
}

map<ll,vector<pair<ll,int>>> pfacs;
void f(vector<pair<ll,int>>& vec, ll x, int i) {
    if (i == v.size()) {
        pfacs[x] = vec;
        return;
    }
    ll mult = 1;
    for (int j = 0; j <= v[i].second; j++) {
        vec.push_back({v[i].first,j});
        f(vec,x*mult,i+1);
        vec.pop_back();
        mult *= v[i].first;
    }
}

const int M = 998244353;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int fac[60], ifac[60];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < 60; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = inverse(fac[i]);
    }
    cin >> D >> q;
    factor(D);
    for (auto p: primes) v.push_back(p);
    vector<pair<ll,int>> vec;
    f(vec,1,0);
    auto calc = [&](ll u, ll v) { //u <= v
        //cout << u << ' ' << v << ":\n";
        vector<int> d1, d2;
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < pfacs[u].size(); i++) {
            int d = pfacs[v][i].second-pfacs[u][i].second;
            //cout << d << ' ';
            if (d >= 0) {
                d1.push_back(d);
                sum1 += d;
            }
            else {
                d2.push_back(abs(d));
                sum2 += abs(d);
            }
        }
        int ans = fac[sum1];
        for (auto d: d1) {
            ans = mult(ans,ifac[d]);
        }
        ans = mult(ans,fac[sum2]);
        for (auto d: d2) {
            ans = mult(ans,ifac[d]);
        }
        return ans;
    };
    while (q--) {
        ll u, v; cin >> u >> v;
        //cout << __gcd(u,v) << '\n';
        if (u > v) swap(u,v);
        cout << calc(u,v) << '\n';
    }
    /*
    for (auto p: pfacs) {
        cout << p.first << endl;
        for (auto q: p.second) {
            cout << q.first << ' ' << q.second << endl;
        }
    }
    */
}
