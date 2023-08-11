#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 1e5+5;
int N, M;
vector<pair<int, int>> adj[maxn];
vector<array<int, 3>> E;
int C[maxn];

struct DSU {
  int n;
  vector<int> par;
  ll s;
  vector<ll> sum;
  DSU(int _n, ll _s) : s(_s) {
    n = _n;
    par.resize(n+1, -1);
    sum.resize(n+1, 0);
    for (int i = 1; i <= n; i++) sum[i] = C[i];
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y, int w) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (s-sum[x] > w && s-sum[y] > w) return false;
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    sum[x] += sum[y];
    return true;
  }

  int getsz(int i) {
    return -par[Find(i)];
  }
};

bool check(ll s) {
  DSU dsu(N, s);
  REP(5) {
    for (auto [w, i, j]: E) {
      dsu.Union(i, j, w);
    }
  }

  return dsu.getsz(1) == N;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  ll sum = 0;
  FOR(i, 1, N+1) {
    cin >> C[i];
    sum += C[i];
  }
  REP(M) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
    E.push_back({w, a, b});
  }
  sort(all(E), greater());

  if (!check(1 + sum)) {
    cout << -1 << '\n';
    return 0;
  }
  int lo = 1, hi = 1e9+5;
  while (lo + 1 < hi) {
    int mid = std::midpoint(lo, hi);
    (check(mid + sum) ? lo : hi) = mid;
  }
  cout << lo << '\n';
}
