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

struct Tree {
  static const int maxn = 105;
  int d[maxn][maxn];
  int adj[maxn][maxn];

  Tree(int n, vector<array<int, 2>> edges) {
    memset(d, -1, sizeof d);
    memset(adj, 0, sizeof adj);
    for (auto [u, v]: edges) {
      adj[u][v] = 1;
      adj[v][u] = 1;
    }
    F0R(i, n) {
      d[i][i] = 0;
      queue<int> q; q.push(i);
      while (!q.empty()) {
        int f = q.front(); q.pop();
        F0R(j, n) if (adj[f][j] && d[i][j] == -1) {
          d[i][j] = d[i][f] + 1;
          q.push(j);
        }
      }
    }
  }
};

std::optional<vector<array<int, 2>>> solve() {
  int N; cin >> N;
  vector<vector<vector<int>>> d(N, vector<vector<int>>(N, vector<int>(N)));
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      for (int k = 0; k < N; k++) {
        char c; cin >> c;
        d[k][i][j] = d[k][j][i] = c-'0';
      }
    }
  }

  vector<vector<vector<int>>> classes(N);
  for (int i = 0; i < N; i++) {
    vector<bool> vis(N, false);
    for (int j = 0; j < N; j++) {
      if (!vis[j]) {
        vector<int> adj = {j};
        for (int k = 0; k < N; k++) {
          if (d[i][j][k]) adj.push_back(k);
        }

        for (auto a: adj) for (auto b: adj) {
          if (a != b && !d[i][a][b]) {
            // not a clique; exit
            return std::nullopt;
          }
        }

        for (int k: adj) vis[k] = true;
        classes[i].push_back(adj);
      }
    }
  }

  int min_ecc = 2e9;
  vector<int> centers;
  F0R(i, N) {
    if (ckmin(min_ecc, sz(classes[i]))) {
      centers = {i};
    }
    else if (min_ecc == sz(classes[i])) {
      centers.push_back(i);
    }
  }

  vector<array<int, 2>> edges;
  auto get_class = [&](int i, int j) -> vector<int> {
    for (auto v: classes[i]) {
      if (find(all(v), j) != v.end()) {
        return v;
      }
    }
    assert(false);
  };

  vector<bool> vis(N, false);
  auto rec = y_combinator([&](auto rec, int i, int p) -> void {
    vis[i] = true;
    edges.push_back({i, p});
    auto v = get_class(i, p);
    for (auto j: v) if (j != p && !vis[j]) {
      rec(j, i);
    }
  });

  if (sz(centers) > 2) {
    // cannot have more than 2 centers, exit
    return std::nullopt;
  }
  else if (sz(centers) == 1) {
    int i = centers[0];
    vis[i] = true;
    F0R(j, N) if (sz(classes[j]) == min_ecc + 1) {
      rec(j, i);
    }
  }
  else {
    int i1 = centers[0];
    int i2 = centers[1];
    vis[i1] = vis[i2] = true;
    edges.push_back({i1, i2});
    auto v1 = get_class(i1, i2);
    for (auto j: v1) if (j != i2) rec(j, i1);
    auto v2 = get_class(i2, i1);
    for (auto j: v2) if (j != i1) rec(j, i2);
  }

  // Check constructed tree against constraints
  if (sz(edges) < N-1) {
    return std::nullopt;
  }
  Tree tree(N, edges);
  F0R(k, N) {
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        if (d[k][i][j] && tree.d[k][i] != tree.d[k][j]) {
          return std::nullopt;
        }
        else if (!d[k][i][j] && tree.d[k][i] == tree.d[k][j]) {
          return std::nullopt;
        }
      }
    }
  }
  return edges;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    auto edges = solve();
    if (edges) {
      cout << "Yes\n";
      for (auto [u, v]: *edges) {
        cout << u+1 << ' ' << v+1 << '\n';
      }
    }
    else cout << "No\n";
  }
}
