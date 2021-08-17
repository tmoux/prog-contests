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

struct Fenwick
{
    int n;
    vector<ll> bit;
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, ll x) {
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    ll sum(int i) {
        ll r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};

const int maxn = 5e5+5;
int N, M;

vector<int> adj[maxn];

int v[maxn];

int pt = 1;
int tin[maxn], tout[maxn];
void dfs(int i) {
  tin[i] = pt++;
  for (int j: adj[i]) {
    dfs(j);
  }
  tout[i] = pt;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  Fenwick fen(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> v[i];
    if (i > 1) {
      int par; cin >> par;
      adj[par].push_back(i);
    }
  }
  dfs(1);
  for (int i = 1; i <= N; i++) {
    fen.add(tin[i],v[i]);
    fen.add(tin[i]+1,-v[i]);
  }
  F0R(_, M) {
    char c; cin >> c;
    if (c == 'p') {
      int a, x; cin >> a >> x;
      fen.add(tin[a]+1,x);
      fen.add(tout[a],-x);
    }
    else if (c == 'u') {
      int a; cin >> a;
      cout << fen.sum(tin[a]) << '\n';
    }
  }
}
