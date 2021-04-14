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

const int maxn = 2e7+7;
int spf[maxn];
int val[maxn];

void solve() {
  ll c, d, x; cin >> c >> d >> x;
  ll ans = 0;
  auto add = [&](ll g) {
    ll xp = x/g;
    if ((xp+d) % c == 0) {
      ll AB = (xp+d)/c;
      //cout << "found " << AB << '\n';
      ans += 1<<val[AB];
    }
  };
  for (ll i = 1; i*i <= x; i++) {
    if (x % i == 0) {
      add(i);
      if (x/i != i) add(x/i);
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
  for (int i = 2; i < maxn; i++) {
    int j = i/spf[i];
    val[i] = val[j];
    if (spf[i] != spf[j]) val[i]++;
  }
  /*
  for (int i = 0; i <= 10; i++) {
    cout << i << ": " << spf[i] << ' ' << val[i] << '\n';
  }
  return 0;
  */
  int t; cin >> t;
  while (t--) solve();
}
