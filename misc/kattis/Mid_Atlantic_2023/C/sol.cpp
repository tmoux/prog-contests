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
  int N, M; cin >> N >> M;
  vector<string> g(N);
  F0R(i, N) {
    cin >> g[i];
  }

  vector<vector<int>> dist(N, vector<int>(M, 1e9));
  queue<pair<int, int>> q;

  auto valid = [&](int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
  };

  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};
  F0R(i, N) {
    F0R(j, M) {
      if (g[i][j] == '-') continue;
      bool ok = false;
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (!valid(ni, nj) || g[ni][nj] == '-') ok = true;
      }
      if (ok) {
        q.push({i, j});
        dist[i][j] = 1;
      }
    }
  }

  if (q.empty()) {
    cout << 0 << '\n';
  }
  else {
    int ans = 0;
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();
      ckmax(ans, dist[i][j]);
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (valid(ni, nj) && g[ni][nj] == 'X' && dist[ni][nj] > dist[i][j] + 1) {
          q.push({ni, nj});
          dist[ni][nj] = dist[i][j] + 1;
        }
      }
    }
    cout << ans << '\n';
  }
}
