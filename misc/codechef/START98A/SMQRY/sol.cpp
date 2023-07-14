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

struct DSU {
  int n;
  vector<int> par;
  vector<int> diam;
  vector<pair<int, int>> ends;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
    diam.resize(n+1, 0);
    ends.resize(n+1);
    F0R(i, n+1) ends[i] = {i, i};
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  int size(int x) {
    return -par[Find(x)];
  }
};

void solve() {
  int N, Q; cin >> N >> Q;
  DSU dsu(N);

  vector<vector<int>> adj(N+1);
  int score = 0;
  int sumDiam = 0;

  const int maxk = 18;
  vector<vector<int>> par(maxk, vector<int>(N+1, -1));
  vector<int> depth(N+1);

  auto lca = [&](int a, int b) -> int {
    if (depth[a] > depth[b]) swap(a, b);
    for (int k = maxk-1; k >= 0; k--) {
      int bb = par[k][b];
      if (bb != -1 && depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      int bb = par[k][b];
      if (aa != bb) {
        a = aa;
        b = bb;
      }
    }
    return par[0][a];
  };

  auto dist = [&](int a, int b) -> int {
    int lc = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[lc];
  };

  auto DFS = y_combinator([&](auto DFS, int i, int p, int d) -> void {
    depth[i] = d;
    par[0][i] = p;
    FOR(k, 1, maxk) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) {
      if (j != p) {
        DFS(j, i, d+1);
      }
    }
  });

  auto merge = [&](int x, int y) -> void {
    // make x parent of y
    // reroot y's subtree
    adj[x].push_back(y);
    adj[y].push_back(x);
    DFS(y, x, depth[x] + 1);
  };

  vector<bool> vis(N+1);
  REP(Q) {
    int u, v; cin >> u >> v;
    int x = score ^ u;
    int y = score ^ v;
    assert(1 <= x && x <= N);
    assert(1 <= y && y <= N);
    if (dsu.size(x) < dsu.size(y)) swap(x, y);

    sumDiam -= dsu.diam[dsu.Find(x)];
    sumDiam -= dsu.diam[dsu.Find(y)];

    auto [a1, a2] = dsu.ends[dsu.Find(x)];
    auto [b1, b2] = dsu.ends[dsu.Find(y)];
    vector<int> V = {a1, a2, b1, b2};

    merge(x, y);

    pair<int, pair<int, int>> best = {-1, {-1, -1}};
    F0R(i, 4) {
      FOR(j, i+1, 4) {
        int a = V[i], b = V[j];
        ckmax(best, {dist(a, b), {a, b}});
      }
    }

    dsu.Union(x, y);
    x = dsu.Find(x);
    dsu.diam[x] = best.first;
    dsu.ends[x] = best.second;

    sumDiam += dsu.diam[x];
    score ^= sumDiam;
  }
  cout << score << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
