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

const int maxn = 10005;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void solve() {
  int N, K;
  cin >> N >> K;
  vector<vector<int>> g(N, vector<int>(N, 0));
  vector<pair<int, int>> pos(N * N + 1);
  auto valid = [&](int i, int j) { return 0 <= i && i < N && 0 <= j && j < N; };
  int k = 0;
  int x = 0, y = 0;
  for (int i = 1; i <= N * N; i++) {
    g[x][y] = i;
    pos[i] = {x, y};
    int nx = x + dx[k];
    int ny = y + dy[k];
    if (!valid(nx, ny) || g[nx][ny] > 0) {
      k = (k + 1) % 4;
    }
    x = x + dx[k];
    y = y + dy[k];
  }

  int L = (N * N - 1) - K;
  if (K < N - 1) {
    cout << "IMPOSSIBLE\n";
  } else if (L % 2 == 0) {
    int i = 1;
    vector<pair<int, int>> ans;
    while (L > 0) {
      auto [x, y] = pos[i];
      for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (valid(nx, ny)) {
          int ni = g[nx][ny];
          if (i + 1 < ni) {
            int add = ni - (i + 1);
            if (L >= add) {
              L -= add;
              ans.push_back({i, ni});
              i = ni;
              goto done;
            }
          }
        }
      }
      i++;
    done:;
    }
    cout << sz(ans) << '\n';
    for (auto [x, y] : ans) {
      cout << x << ' ' << y << '\n';
    }
  } else {
    cout << "IMPOSSIBLE\n";
  }

  /*
  cout << '\n';
  F0R(i, N) {
    F0R(j, N) {
      cout << g[i][j] << ' ';
    }
    cout << '\n';
  }
  */
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  FOR(tt, 1, T + 1) {
    cout << "Case #" << tt << ": ";
    solve();
  }
}
