#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}

struct Edge {
  int to;
  int w;
};

void solve() {
  int n, m; cin >> n >> m;
  map<pair<int,int>, int> edges;
  vector<vector<Edge>> adj(n);
  vector<vector<int>> all_adj(n);
  REP(n-1) {
    int x, y, v; cin >> x >> y >> v;
    x--; y--;
    all_adj[x].push_back(y);
    all_adj[y].push_back(x);
    if (v != -1) {
      int par = __builtin_popcount(v) % 2;
      adj[x].push_back({y, par});
      adj[y].push_back({x, par});
      edges[{x, y}] = v;
      edges[{y, x}] = v;
    }
  }
  REP(m) {
    int a, b, p; cin >> a >> b >> p;
    a--; b--;
    assert(p == 0 || p == 1);
    int par = p;
    adj[a].push_back({b, par});
    adj[b].push_back({a, par});
  }

  bool poss = true;
  vector<int> val(n, -1);
  auto dfs = y_combinator([&](auto dfs, int i, int v) -> void {
    val[i] = v;
    for (auto [j, w]: adj[i]) {
      if (val[j] == -1) {
        dfs(j, v^w);
      }
      else if (val[j] != (val[i]^w)) {
        poss = false;
      }
    }
  });

  F0R(i, n) {
    if (val[i] == -1) dfs(i, 0);
  }

  if (poss) {
    cout << "YES\n";
    map<pair<int,int>, int> ans; 
    auto recon = y_combinator([&](auto recon, int i, int p) -> void {
      for (int j: all_adj[i]) if (j != p) {
        if (edges.count({i, j})) {
          ans[{i, j}] = edges[{i, j}];
        }
        else {
          ans[{i, j}] = val[i] ^ val[j];
        }
        recon(j, i);
      }
    });
    recon(0, 0);
    for (auto [p, v]: ans) {
      cout << p.first+1 << ' ' << p.second+1 << ' ' << v << '\n';
    }
  }
  else {
    cout << "NO\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
