#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
int dp[maxn][maxn], pdp[maxn][maxn];

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

  const int MAGIC = 300;
  FOR(x, 1, P+1) {
    F0R(i, N) F0R(j, M) dp[i][j] = INF;
    if (x == 1 || sz(v[x-1]) * sz(v[x]) > N*M) {
      for (auto [i, j]: v[x]) {
        ckmin(dp[i][j], B[0][i][j] - i - j);
        ckmin(dp[i][j], B[1][i][j] + i - j);
        ckmin(dp[i][j], B[2][i][j] + i + j);
        ckmin(dp[i][j], B[3][i][j] - i + j);
      }
    }
    else {
      for (auto [i, j]: v[x]) {
        for (auto [a, b]: v[x-1]) {
          ckmin(dp[i][j], pdp[a][b] + abs(i - a) + abs(j - b));
        }
      }
    }

    if (x == P) {
      cout << dp[v[x][0].first][v[x][0].second] << '\n';
    }

    if (sz(v[x]) * sz(v[x+1]) > N*M) {
      F0Rd(i, N) { // {{{
        F0Rd(j, M) {
          B[0][i][j] = dp[i][j] + i + j;
          if (i + 1 < N) ckmin(B[0][i][j], B[0][i+1][j]);
          if (j + 1 < M) ckmin(B[0][i][j], B[0][i][j+1]);
          if (i + 1 < N && j + 1 < M) ckmin(B[0][i][j], B[0][i+1][j+1]);
        }
      }
      F0R(i, N) {
        F0Rd(j, M) {
          B[1][i][j] = dp[i][j] - i + j;
          if (i > 0) ckmin(B[1][i][j], B[1][i-1][j]);
          if (j + 1 < M) ckmin(B[1][i][j], B[1][i][j+1]);
          if (i > 0 && j + 1 < M) ckmin(B[1][i][j], B[1][i-1][j+1]);
        }
      }
      F0R(i, N) {
        F0R(j, M) {
          B[2][i][j] = dp[i][j] - i - j;
          if (i > 0) ckmin(B[2][i][j], B[2][i-1][j]);
          if (j > 0) ckmin(B[2][i][j], B[2][i][j-1]);
          if (i > 0 && j > 0) ckmin(B[2][i][j], B[2][i-1][j-1]);
        }
      }
      F0Rd(i, N) {
        F0R(j, M) {
          B[3][i][j] = dp[i][j] + i - j;
          if (i + 1 < N) ckmin(B[3][i][j], B[3][i+1][j]);
          if (j > 0) ckmin(B[3][i][j], B[3][i][j-1]);
          if (i + 1 < N && j > 0) ckmin(B[3][i][j], B[3][i+1][j-1]);
        }
      } // }}}
    }
    else {
      for (auto [i, j]: v[x]) {
        pdp[i][j] = dp[i][j];
      }
    }
  }
}
