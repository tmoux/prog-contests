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

// Find leaf (minimal cost)
// Rooted at leaf, find adjacent vertex (second highest cost)
// Delete edge and repeat

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // returns true if x and y were not connected
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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<vector<ll>> F(N, vector<ll>(N));
  F0R(i, N) {
    F0R(j, i+1) {
      cin >> F[i][j];
      F[j][i] = F[i][j];
    }
  }

  vector<bool> removed(N, false);
  vector<array<int, 3>> edges;

  auto find_leaf = [&]() -> int {
    int i;
    for (i = 0; i < N; i++) if (!removed[i]) break;
    pair<ll, int> leaf = {1e18, -1};
    F0R(j, N) if (!removed[j]) ckmin(leaf, {F[i][j], j});
    assert(leaf.second != -1);
    return leaf.second;
  };

  auto find_adjacent = [&](int i) -> int {
    pair<ll, int> adj = {-1, -1};
    F0R(j, N) if (!removed[j] && j != i) ckmax(adj, {F[i][j], j});
    assert(adj.second != -1);
    return adj.second;
  };

  DSU dsu(N);

  auto remove_edge = [&](int i, int j, int sz) -> void {
    assert((F[i][i] - F[i][j]) % sz == 0);
    ll w = (F[i][i] - F[i][j]) / sz;
    assert(w <= 1000000000);
    edges.push_back({i, j, (int)w});
    removed[i] = true;
    dsu.Union(i, j);
  };

  REP(N-1) {
    int i = find_leaf();
    int j = find_adjacent(i);
    remove_edge(i, j, N - dsu.size(i));
  }

  for (auto [u, v, w]: edges) {
    cout << u+1 << ' ' << v+1 << ' ' << w << '\n';
  }
}
