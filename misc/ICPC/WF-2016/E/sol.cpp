//Randomness stuff, ckmin, ckmax are optional--depends on time
#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
  return ((__int128)(a) * b) % M;
	// ll ret = a * b - M * ull(1.L / M * a * b);
	// return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}

bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
    s = __builtin_ctzll(n-1), d = n >> s;
  for (ull a : A) {   // ^ count trailing zeroes
    ull p = modpow(a%n, d, n), i = s;
    assert(p < n);
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n-1 && i != s) {
      return 0;
    }
  }
  return 1;
}

ull pollard(ull n) {
  auto f = [n](ull x) { return modmul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}
vector<ull> factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), all(r));
  return l;
}

vector<pair<ull, int>> v;
vector<ull> factors;
void rec(int i, ull cur) {
  if (i == sz(v)) {
    factors.push_back(cur);
    return;
  }
  else {
    ull mult = 1;
    for (int j = 0; j <= v[i].second; j++) {
      rec(i+1, cur * mult);
      mult *= v[i].first;
    }
  }
}

ull Y, L;
bool test(ull b) {
  if (b < 10) return true;
  vector<ull> d;
  ll y = Y;
  while (y > 0) {
    if (y % b >= 10) return false;
    d.push_back(y % b) ;
    y /= b;
  }
  ull mult = 1;
  ull res = 0;
  for (auto digit: d) {
    res += digit * mult;
    mult *= 10;
  }
  return res >= L;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cout << isPrime(333333333333333331) << endl;
  cin >> Y >> L;

  ull ans = 10;
  for (ull x = Y; x > Y-10; x--) {
    map<ull, int> mp;

    ull y = x;
    auto primes = factor(y);
    for (auto p: primes) mp[p]++;
    v.clear(); factors.clear();
    for (auto p: mp) v.push_back(p);
    rec(0, 1);

    for (auto b: factors) {
      if (test(b)) {
        ckmax(ans, b);
      }
    }
  }
  cout << ans << '\n';
	return 0;
}
