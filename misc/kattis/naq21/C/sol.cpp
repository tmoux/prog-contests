#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

// Returns a * b and whether this product overflows
pair<ll, bool> mult_overflow(ll a, ll b) {
  ll x = a * b;
  return {x, a != 0 && x / a != b};
}

ll n;
bool notPrime[100];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<ll> primes;
    ll prod = 1;
    for (int i = 2; i < 100; i++) {
        if (!notPrime[i]) {
            auto [np, overflow] = mult_overflow(prod, i);
            if (overflow || np > n) break;
            prod = np;
            primes.push_back(i);
            for (int j = i+i; j < 100; j += i) {
                notPrime[j] = true;
            }
        }
    }

    ll num = 0;
    int N = sz(primes);
    for (int mask = 1; mask < (1<<N); mask++) {
        int cnt = 0;
        ll x = 1;
        for (int i = 0; i < N; i++) {
            if (mask & (1<<i)) {
                cnt++;
                x *= primes[i];
            }
        }
        ll add = prod/x;
        if (cnt&1) num += add;
        else num -= add;
    }
    ll den = prod;
    ll gc = __gcd(num, den);
    num /= gc;
    den /= gc;

    cout << num << '/' << den << '\n';
}
