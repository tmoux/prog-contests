#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
 
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
 
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
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
template<typename T, typename U>
ostream& operator<<(ostream& o, const map<T,U>& mp) {
  o << "{";
  for (auto it = mp.begin(); it != mp.end(); ++it) {
    o << "(" << it->first << ", " << it->second << ")";
    if (next(it) != mp.end()) o << ", ";
  }
  o << "}";
  return o;
}

const int maxn = 2e5+5, M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

bool isComposite[maxn];
int spf[maxn], quot[maxn];
void sieve() {
  for (int i = 2; i <= 200000; i++) {
    spf[i] = 2;
    quot[i] = i/2;
  }
  for (int i = 3; i <= 200000; i += 2) {
    if (!isComposite[i]) {
      spf[i] = i;
      quot[i] = 1;
      for (int j = i; j <= 200000; j += i) {
        if (!isComposite[j]) {
          isComposite[j] = true;
          spf[j] = i;
          quot[j] = j/i;
        }
      }
    }
  }
}

multiset<int> ms[maxn];
map<int,int> primes[maxn];
int ans = 1;
int n, q;

map<int,int> factors(int x) {
  map<int,int> res;
  while (x > 1) {
    res[spf[x]]++;
    x = quot[x];
  }
  return res;
}

int prime_min(int x) {
  return ms[x].size() < n ? 0 : *ms[x].begin();
}

void update(int i, int x) {
  auto mp = factors(x);
  for (auto p: mp) {
    int prime = p.f;
    int add = p.s;
    int prev_cnt = prime_min(prime);
    if (primes[i][prime] != 0) {
      auto it = ms[prime].find(primes[i][prime]);
      ms[prime].erase(it);
    }
    primes[i][prime] += add;
    ms[prime].insert(primes[i][prime]);
    int new_cnt = prime_min(prime);
    if (new_cnt > prev_cnt) {
      ans = mult(ans,modexp(prime,new_cnt-prev_cnt));
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  sieve();
  cin >> n >> q;
  F0R(i,n) {
    int x; cin >> x;
    update(i,x);
  }
  F0R(_,q) {
    int i, x; cin >> i >> x;
    i--;
    update(i,x);
    cout << ans << '\n';
  }
}
