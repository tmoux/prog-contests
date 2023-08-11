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

void solve() {
  int n, l, r; cin >> n >> l >> r;
  map<int,int> L, R;
  for (int i = 0; i < l; i++) {
    int c; cin >> c;
    L[c]++;
  }
  for (int i = 0; i < r; i++) {
    int c; cin >> c;
    R[c]++;
  }
  for (auto p: L) {
    int mn = min(L[p.first],R[p.first]);
    L[p.first] -= mn;
    R[p.first] -= mn;
  }
  int lc = 0, rc = 0;
  for (auto p: L) lc += p.second;
  for (auto p: R) rc += p.second;
  if (lc < rc) {
    swap(lc,rc);
    swap(L,R);
  }
  int ans = 0;
  int move = (lc-rc)/2;
  for (auto p: L) {
    int cnt = min(move,p.second/2);
    L[p.first] -= cnt*2;
    move -= cnt;
    ans += cnt;
  }
  int tot = 0;
  for (auto p: L) tot += p.second;
  ans += tot;

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
