#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int maxk = 18;
  int n; cin >> n;
  vector<vector<int>> adj(n);
  vector<vector<int>> par(maxk, vector<int>(n, -1));
  vector<int> depth(n);
  REP(n-1) {
    int a, b; cin >> a >> b;
    a--; b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  auto dfs = y_combinator([&](auto dfs, int i, int p, int d) -> void {
    depth[i] = d;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      if (par[k-1][i] == -1) par[k][i] = -1;
      else par[k][i] = par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
      dfs(j, i, d+1);
    }
  });
  dfs(0, -1, 0);

  auto lca = [&](int a, int b) -> int {
    if (depth[a] > depth[b]) swap(a, b);
    F0Rd(k, maxk) {
      int bb = par[k][b];
      if (b != -1 && depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    F0Rd(k, maxk) {
      int aa = par[k][a];
      int bb = par[k][b];
      if (aa != bb) {
        a = aa;
        b = bb;
      }
    }
    return par[0][a];
  };

  auto len = [&](int a, int b) -> int {
    int lc = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[lc] + 1;
  };

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 2*i; j <= n; j += i) {
      ans += len(i-1, j-1);
    }
  }
  cout << ans << '\n';
}
