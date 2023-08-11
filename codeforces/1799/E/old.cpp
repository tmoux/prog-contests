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
int dp[maxn][maxn][maxn][2][2];
tuple<int, int, int, int> recon[maxn][maxn][maxn][2][2];

void solve() {
  int N, M; cin >> N >> M;
  vector<string> g(N);
  vector<vector<int>> p(N, vector<int>(M));
  int mnR = 1e9, mxR = -1e9;
  vector<int> mnC(N, 1e9), mxC(N, -1e9);
  F0R(i, N) {
    cin >> g[i];
    // g[i] = string(M, '.');
    // if (i == 0) g[i][0] = '#';
    // if (i == N-1) g[i][M-1] = '#';
    if (g[i].find('#') != string::npos) {
      ckmin(mnR, i);
      ckmax(mxR, i);
    }
    F0R(j, M) {
      p[i][j] = g[i][j] == '#' ? 0 : 1;
      if (j > 0) p[i][j] += p[i][j-1];
      if (g[i][j] == '#') {
        ckmin(mnC[i], j);
        ckmax(mxC[i], j);
      }
    }
  }
  for (int i = N-2; i >= 0; i--) {
    // ckmin(mnC[i], mnC[i+1]);
    // ckmax(mxC[i], mxC[i+1]);
  }
  auto getsum = [&](int i, int l, int r) {
    return p[i][r] - (l == 0 ? 0 : p[i][l-1]);
  };

  const int INF = 1e9;
  for (int i = mnR; i <= mxR; i++) {
    for (int l = 0; l < M; l++) {
      for (int r = l; r < M; r++) {
        for (int j: {0, 1}) {
          for (int k: {0, 1}) {
            dp[i][l][r][j][k] = INF;
            recon[i][l][r][j][k] = {-1, -1, -1, -1};
          }
        }
      }
    }
  }
  // F0R(i, N) {
  //   cout << i << ": " << mnC[i] << ' ' << mxC[i] << endl;
  // }
  dp[mnR][mnC[mnR]][mxC[mnR]][0][0] = getsum(mnR, mnC[mnR], mxC[mnR]);
  // DEBUG(mnC[mnR]);
  // DEBUG(mxC[mnR]);
  pair<int, tuple<int, int, int, int>> best = {INF, {}};
  for (int i = mnR; i < mxR; i++) {
    for (int l = 0; l < M; l++) {
      for (int r = l; r < M; r++) {
        int nl = min(r, mnC[i+1]);
        int nr = max(l, mxC[i+1]);
        // 0 -> 0, 0 -> 0, 1 -> 1

        // L < l: 0 -> 0
        // L = l: 0 -> 0, 1 -> 1
        // L > l: 0 -> 1, 1 -> 1
        //
        // 0 : 0 -> 0 : 0, 1
        // 1 : 1 -> 1 : 1, 2
        // 2 : 0 -> 1 : 2
        auto canl = [&](int il, int L, int l) {
          if (il == 0) return L <= l;
          else if (il == 1) return L >= l;
          else return L > l;
        };
        auto canr = [&](int ir, int R, int r) {
          if (ir == 0) return R >= r;
          else if (ir == 1) return R <= r;
          else return R < r;
        };

        int C[][2] = {{0, 0}, {1, 1}, {0, 1}};
        // for (int L: {nl, min(l, nl)}) {
        //   for (int R: {nr, max(r, nr)}) {
        for (int L = 0; L <= min(r, mnC[i+1]); L++) {
          for (int R = max({L, l, mxC[i+1]}); R < M; R++) {
            for (int il : {0, 1, 2}) {
              for (int ir : {0, 1, 2}) {
                if (canl(il, L, l) && canr(ir, R, r)) {
                  if (ckmin(dp[i+1][L][R][C[il][1]][C[ir][1]],
                            dp[ i ][l][r][C[il][0]][C[ir][0]] + getsum(i+1, L, R))) {
                    recon[i+1][L][R][C[il][1]][C[ir][1]] = {l, r, C[il][0], C[ir][0]};
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  for (int l = 0; l < M; l++) {
    for (int r = l; r < M; r++) {
      for (int j: {0, 1}) {
        for (int k: {0, 1}) {
          ckmin(best, {dp[mxR][l][r][j][k], {l, r, j, k}});
        }
      }
    }
  }
  assert(best.first != INF);

  vector<string> ans(N, string(M, '.'));
  int L, R, a, b;
  tie(L, R, a, b) = best.second;
  for (int i = mxR; i >= mnR; i--) {
    for (int j = L; j <= R; j++) {
      ans[i][j] = '#';
    }
    tie(L, R, a, b) = recon[i][L][R][a][b];
  }

  F0R(i, N) {
    cout << ans[i] << '\n';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
