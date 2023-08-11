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

ll solve() {
  int N, M; cin >> N >> M;
  vector<vector<pair<int, ll>>> adj(N);
  vector<vector<ll>> edge(N, vector<ll>(N, 1e18));
  REP(M) {
    int u, v, w; cin >> u >> v >> w;
    u--; v--;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
    ckmin(edge[u][v], (ll)w);
    ckmin(edge[v][u], (ll)w);
  }
  auto is_adj = [&](int i, int j) {
    return edge[i][j] < 1e18;
  };
  auto can_trans = [&](int a, int b, int c, int d) {
    return (a == c && (is_adj(b, d) || d == a)) ||
           (b == d && (is_adj(a, c) || c == b));
  };

  auto bfs = [&]() -> vector<vector<int>> {
    vector<vector<int>> dist(N, vector<int>(N, 999999));
    dist[0][N-1] = dist[N-1][0] = 0;
    queue<pair<int, int>> q;
    q.push({0, N-1}); q.push({N-1, 0});
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();
      // if (i <= j) cout << i+1 << ' ' << j+1 << ": " << dist[i][j] << endl;

      auto upd = [&](int x, int y) {
        if (dist[x][y] > dist[i][j] + 1) {
          dist[x][y] = dist[i][j] + 1;
          q.push({x, y});
        }
      };
      F0R(k, N) if (can_trans(k, j, i, j)) {
        upd(k, j);
      }
      F0R(k, N) if (can_trans(i, k, i, j)) {
        upd(i, k);
      }
    }
    return dist;
  };

  auto dist = bfs();

  ll ans = 1e18;
  F0R(i, N) {
    for (auto [j, w]: adj[i]) {
      int d = dist[i][j] + 1;
      // cout << i+1 << ' ' << j+1 << ": " << d << ' ' << d * w << endl;
      ckmin(ans, 1LL * d * w);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
