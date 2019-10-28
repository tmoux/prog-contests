#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M1 = 1e9+7, M2 = 998244353;
int base = 103;
const int N = 1e5+5;
int n, a[N], k;

map<int,int> factors[N];

void factor(int x, int i) {
    for (int j = 2; j*j <= x; j++) {
        if (x % j == 0) {
            while (x % j == 0) {
                factors[i][j]++;
                x /= j;
            }
            factor(x,i);
            return;
        }
    }
    if (x > 1) {
        factors[i][x]++;
    }
}

int mult(int a, int b, int M) {
    return (1LL*a*b) % M;
}

void madd(int& a, int b, int M) {
    a += b;
    if (a > M) a -= M;
}

int modexp(int a, int b, int M) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a,M);
        a = mult(a,a,M);
        b >>= 1;
    }
    return res;
}

pair<int,int> hsh(const map<int,int>& mp) {
    pair<int,int> res = {0,0};
    for (auto& p: mp) {
        if (p.second == 0) continue;
        madd(res.first,mult(p.second,modexp(base,p.first,M1),M1),M1);       
        madd(res.second,mult(p.second,modexp(base,p.first,M2),M2),M2);       
    }
    return res;
}

pair<int,int> revhsh(const map<int,int>& mp) {
    pair<int,int> res = {0,0};
    for (auto& p: mp) {
        if (p.second == 0) continue;
        madd(res.first,mult(k-p.second,modexp(base,p.first,M1),M1),M1);       
        madd(res.second,mult(k-p.second,modexp(base,p.first,M2),M2),M2);       
    }
    return res;
}

pair<int,int> hashes[N], c_hash[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    mt19937 gen(time(0));
    base = 103 + (gen() % 1000);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        factor(a[i],i);
        for (auto& p: factors[i]) {
            p.second %= k;
            //cout << p.first << ' ' << p.second << '\n';
        }
        //cout << '\n';
        hashes[i] = hsh(factors[i]);
        c_hash[i] = revhsh(factors[i]);
        /*
        cout << i << ": " << hashes[i].first << ' ' << hashes[i].second << '\n';
        cout << i << ": " << c_hash[i].first << ' ' << c_hash[i].second << '\n';
        */
    }
    ll ans = 0;
    map<pair<int,int>,int> seen;
    for (int i = 1; i <= n; i++) {
        ans += seen[c_hash[i]];
        //cout << i << ": " << seen[c_hash[i]] << '\n';
        seen[hashes[i]]++;
    }
    cout << ans << '\n';
}

