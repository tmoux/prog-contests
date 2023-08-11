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

const int maxn = 2e5+5;
int n, m;
int deg[maxn];

int numTerminal;
void update(int i, int d) {
  if (deg[i] == 0 && deg[i]+d > 0) numTerminal--;
  else if (deg[i] > 0 && deg[i]+d == 0) numTerminal++;
  deg[i] += d;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  numTerminal = n;
  F0R(_, m) {
    int a, b; cin >> a >> b;
    if (a > b) swap(a,b);
    update(a,1);
  }
  int q; cin >> q;
  while (q--) {
    int t; cin >> t;
    if (t == 1) {
      int a, b; cin >> a >> b;
      if (a > b) swap(a,b);
      update(a,1);
    }
    else if (t == 2) {
      int a, b; cin >> a >> b;
      if (a > b) swap(a,b);
      update(a,-1);
    }
    else {
      cout << numTerminal << '\n';
    }
  }
}
