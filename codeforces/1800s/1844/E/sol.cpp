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

struct Graph {
  int N;
  vector<vector<pair<int, int>>> adj;
  Graph (int _N) : N(_N) {
    adj.resize(N+1);
  }
  void add_edge(int i, int j, int v) {
    adj[i].push_back({j, v});
    adj[j].push_back({i, v});
  }

  bool check() {
    bool poss = true;
    vector<int> color(N+1, -1);
    auto dfs = y_combinator([&](auto dfs, int i, int c) -> void {
      color[i] = c;
      for (auto [j, v]: adj[i]) {
        if (color[j] == -1) {
          dfs(j, c ^ v);
        }
        else if (color[j] != (c ^ v)) {
          poss = false;
        }
      }
    });
    F0R(i, N+1) {
      if (color[i] == -1) dfs(i, 0);
    }
    return poss;
  }
};

bool solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<array<int, 3>> V;
  F0R(i, K) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    int X = min(x1, x2);
    int Y = min(y1, y2);

    int v = 0;
    if ((x1 == X && y1 == Y) || (x2 == X && y2 == Y)) {
      v = 0;
    }
    else v = 1;
    V.push_back({X, Y, v});
  }

  // check if no immediate contradictions
  F0R(i, K) {
    auto [x1, y1, v1] = V[i];
    FOR(j, i+1, K) {
      auto [x2, y2, v2] = V[j];
      if (x1 == x2 && y1 == y2 && v1 != v2) return false;
    }
  }

  Graph g1(M), g2(N);
  F0R(i, K) {
    auto [x1, y1, v1] = V[i];
    FOR(j, i+1, K) {
      auto [x2, y2, v2] = V[j];
      if (x1 == x2) {
        int ymin = min(y1, y2);
        int ymax = max(y1, y2);
        g1.add_edge(ymin-1, ymax-1, v1 ^ v2);
      }
      else if (y1 == y2) {
        int xmin = min(x1, x2);
        int xmax = max(x1, x2);
        g2.add_edge(xmin-1, xmax-1, v1 ^ v2);
      }
    }
  }

  return g1.check() && g2.check();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "YES" : "NO") << '\n';
}
