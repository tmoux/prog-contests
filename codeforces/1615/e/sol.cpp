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

ll solve() {
  int n, k;
  cin >> n >> k;
  vector<vector<int>> adj(n);
  REP(n-1) {
    int a, b; cin >> a >> b;
    a--; b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> par(n, 0);
  vector<pair<int,int>> leafs;
  y_combinator([&](auto dfs, int i, int p, int d) -> void {
    par[i] = p;
    if (i != 0 && sz(adj[i]) == 1) {
      leafs.push_back({d, i});
    }
    for (int j: adj[i]) if (j != p) {
      dfs(j, i, d+1);
    }
  })(0, 0, 0);

  auto solve = [&](int r, int b) -> ll {
    b = min(b, n/2);
    int w = n-r-b;
    return 1LL*w*(r-b);
  };

  int num_leafs = sz(leafs);
  if (num_leafs <= k) {
    int r = min(max(num_leafs, n/2), k);
    return solve(r, 0);
  }
  else {
    vector<bool> vis(n, false);
    auto color = y_combinator([&](auto color, int i) -> int {
      vis[i] = true;
      if (vis[par[i]]) return 1;
      else return 1 + color(par[i]);
    });
    sort(all(leafs), greater<pair<int,int>>());
    vector<pair<int,int>> vs;
    for (auto [_, i]: leafs) {
      int c = color(i);
      //cout << i+1 << ": " << c << endl;
      vs.push_back({c, i});
    }

    sort(all(vs), greater<pair<int,int>>());
    int b = n, r = 0;

    ll ans = -1e18;
    for (int i = 0; i < k; i++) {
      r++;
      b -= vs[i].first;

      ckmax(ans, solve(r, b));
    }
    return ans;
  }
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cout << solve() << '\n';
}
