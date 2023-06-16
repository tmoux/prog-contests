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

const int MX = 305;
int dp[7][MX][MX];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M, K; cin >> N >> M >> K;
  vector<array<int, 2>> A(N);
  F0R(i, N) {
    cin >> A[i][1] >> A[i][0];
  }

  dp[0][0][0] = 1;
  F0R(idx, N) {
    auto [a, b] = A[idx];
    for (int k = 5; k >= 0; k--) {
      F0R(i, MX) {
        F0R(j, MX) {
          // if (dp[k][i][j]) {
          //   cout << k << ' ' << i << ' ' << j << ": " << dp[k][i][j] << endl;
          // }
          for (int r = 1; r+k <= 6; r++) {
            if (dp[k][i][j] && i + r*a < MX && j + r*b < MX) {
              // cout << "OK " << endl;
              // cout << k+r << ' ' << i+r*a << ' ' << j+r*b << endl;
              dp[k+r][i+r*a][j+r*b] = 1;
            }
          }
        }
      }
    }
  }

  int ans = 0;
  F0R(k, K+1) {
    F0R(i, MX) {
      F0R(j, MX) {
        if (dp[k][i][j] && j * M == i) {
          ckmax(ans, j);
        }
      }
    }
  }
  cout << ans << '\n';
}
