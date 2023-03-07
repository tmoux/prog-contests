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

const string S = "SATELLITE";
const int L = 9;
const int maxn = 300;

ll dp[L+1][L+1][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  for (int n = 0; n < maxn; n++) {
    for (int i = L-1; i >= 0; i--) {
      for (int j = L-1; j >= 0; j--) {
        if (S[i] != S[j]) continue;
        if (i == L-1) {
          dp[i][j][n] = 1;
        }
        else {
          for (int nn = n; nn >= 0; nn--) {
            for (int jj = 0; jj < L; jj++) {
              if (S[jj] == S[i+1] && (jj > j || nn < n)) {
                dp[i][j][n] += dp[i+1][jj][nn];
              }
            }
          }
        }
      }
    }
  }

  string atellite = S.substr(1);
  string ans;

  ll K; cin >> K;
  for (int n = maxn-1; n >= 0; n--) {
    ll c = dp[0][0][n];
    while (K >= c) {
      ans += 'S';
      K -= c;
    }
    ans += atellite;
  }

  assert(sz(ans) <= 5000);
  cout << ans << '\n';
}
