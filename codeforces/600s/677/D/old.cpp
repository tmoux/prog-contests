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

const int maxn = 305;
int N, M, P;
int A[maxn][maxn];
vector<pair<int, int>> v[maxn*maxn];

int B[4][maxn][maxn];
int dp[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> P;
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
      v[A[i][j]].push_back({i, j});
    }
  }

  const int INF = 1e9;
  F0R(k, 4) F0R(i, N) F0R(j, M) if (k != 2) B[k][i][j] = INF;
  B[2][0][0] = 0;
  vector<array<int, 3>> cur = {{0, 0, 0}};
  FOR(x, 1, P+1) {
    F0R(i, N) F0R(j, M) dp[i][j] = INF;
    for (auto [i, j]: v[x]) cur.push_back({i, j, -1});
    sort(all(cur), [](auto a, auto b) {
        if (a[0] != b[0]) return a[0] > b[0];
        return a[1] > b[1];
        });
    int c = INF;
    for (auto [i, j, d]: cur) {
      if (d == -1) ckmin(dp[i][j], c - i - j);
      else ckmin(c, d + i + j);
    }

    sort(all(cur), [](auto a, auto b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
        });
    c = INF;
    for (auto [i, j, d]: cur) {
      if (d == -1) ckmin(dp[i][j], c + i - j);
      else ckmin(c, d - i + j);
    }

    sort(all(cur), [](auto a, auto b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] < b[1];
        });
    c = INF;
    for (auto [i, j, d]: cur) {
      if (d == -1) ckmin(dp[i][j], c + i + j);
      else ckmin(c, d - i - j);
    }

    // sort(all(cur), [](auto a, auto b) {
    //     if (a[0] != b[0]) return a[0] > b[0];
    //     return a[1] < b[1];
    //     });
    // c = INF;
    // for (auto [i, j, d]: cur) {
    //   if (d == -1) ckmin(dp[i][j], c - i + j);
    //   else ckmin(c, d + i - j);
    // }

    cur.clear();
    for (auto [i, j]: v[x]) cur.push_back({i, j, dp[i][j]});
    for (auto [i, j]: v[x]) {
      cout << x << ": " << i << ' ' << j << ": " << dp[i][j] << endl;
    }
    if (x == P) {
      cout << dp[v[x][0].first][v[x][0].second] << '\n';
    }
  }
}
