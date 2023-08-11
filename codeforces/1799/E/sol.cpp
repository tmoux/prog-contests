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

const int maxn = 50;

// Handle case where the two CCs are still not connected.
void fix(int N, int M, vector<string>& ans) {
  vector<vector<pair<int, int>>> comps;
  vector<vector<bool>> vis(N, vector<bool>(M, 0));
  auto dfs = y_combinator([&](auto dfs, int i, int j, vector<pair<int, int>>& v) -> void {
    vis[i][j] = 1;
    v.emplace_back(i, j);
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (0 <= ni && ni < N && 0 <= nj && nj < M) {
        if (ans[ni][nj] == '#' && !vis[ni][nj]) {
          vis[i][j] = 1;
          dfs(ni, nj, v);
        }
      }
    }
  });
  F0R(i, N) {
    F0R(j, M) {
      if (ans[i][j] == '#' && !vis[i][j]) {
        vector<pair<int, int>> v;
        dfs(i, j, v);
        comps.push_back(v);
      }
    }
  }

  if (sz(comps) == 1) return;
  assert(sz(comps) == 2);
  int c1 = comps[0][0].second, c2 = comps[1][0].second;
  if (c1 < c2) {
    auto [x1, y1] = comps[0][0];
    for (auto [x, y]: comps[0]) {
      ckmax(x1, x);
      ckmax(y1, y);
    }
    auto [x2, y2] = comps[1][0];
    for (auto [x, y]: comps[1]) {
      ckmin(x2, x);
      ckmin(y2, y);
    }

    for (int r = x1; r <= x2; r++) {
      ans[r][y1] = '#';
    }
    for (int c = y1; c <= y2; c++) {
      ans[x2][c] = '#';
    }
  }
  else {
    auto [x1, y1] = comps[0][0];
    for (auto [x, y]: comps[0]) {
      ckmax(x1, x);
      ckmin(y1, y);
    }
    auto [x2, y2] = comps[1][0];
    for (auto [x, y]: comps[1]) {
      ckmin(x2, x);
      ckmax(y2, y);
    }

    for (int r = x1; r <= x2; r++) {
      ans[r][y1] = '#';
    }
    for (int c = y1; c >= y2; c--) {
      ans[x2][c] = '#';
    }
  }
}

void fill(int N, int M, vector<string>& g) {
  for (int i = 0; i < N; i++) {
    int mn = 1e9, mx = -1e9;
    for (int j = 0; j < M; j++) {
      if (g[i][j] == '#') {
        ckmin(mn, j);
        ckmax(mx, j);
      }
    }
    for (int j = mn; j <= mx; j++) {
      g[i][j] = '#';
    }
  }
  for (int j = 0; j < M; j++) {
    int mn = 1e9, mx = -1e9;
    for (int i = 0; i < N; i++) {
      if (g[i][j] == '#') {
        ckmin(mn, i);
        ckmax(mx, i);
      }
    }
    for (int i = mn; i <= mx; i++) {
      g[i][j] = '#';
    }
  }
}

void solve() {
  int N, M; cin >> N >> M;
  vector<string> g(N);
  F0R(i, N) {
    cin >> g[i];
  }

  fill(N, M, g);
  fix(N, M, g);
  fill(N, M, g);

  F0R(i, N) {
    cout << g[i] << endl;
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
