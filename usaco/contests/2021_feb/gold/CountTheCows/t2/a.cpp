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

ll pow3[40];
ll sum[40];
void fill_sum(ll d, int k) {
  d = abs(d);
  if (k == 0) sum[k] = d == 0;
  else if (d < pow3[k-1]) {
    fill_sum(d,k-1);
    sum[k] = 3*sum[k-1];
  }
  else {
    fill_sum(d-2*pow3[k-1],k-1);
    sum[k] = sum[k-1];
  }
}

ll prefix(ll x, ll y, int k) {
  if (x < 0 || y < 0) return 0;
  if (k == 0) return 1;
  x %= pow3[k];
  y %= pow3[k];
  if (x < y) swap(x,y);
  ll d = x-y;
  if (d >= pow3[k-1]) {
    if (x < 2*pow3[k-1]) return 0;  
    else if (y < pow3[k-1]) return prefix(x,y,k-1);
    else return sum[k-1];
  }
  else {
    if (x < pow3[k-1]) return prefix(x,y,k-1);
    else if (y < pow3[k-1]) return sum[k-1];
    else if (x < 2*pow3[k-1]) return sum[k-1]+prefix(x,y,k-1);
    else if (y < 2*pow3[k-1]) return 2*sum[k-1];
    else return 2*sum[k-1]+prefix(x,y,k-1);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  pow3[0] = 1;
  for (int i = 1; i < 40; i++) {
    pow3[i] = pow3[i-1] * 3;
  }
  int Q; cin >> Q;
  while (Q--) {
    ll d, x, y; cin >> d >> x >> y;
    fill_sum(x-y,39);
    ll ans = prefix(x+d,y+d,39) - prefix(x-1,y-1,39);
    cout << ans << '\n';
  }
}
