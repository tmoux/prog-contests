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

int solve() {
  int N, M; cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M));
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
    }
  }

  vector<vector<int>> B = A;
  vector<vector<int>> dp = A;

  auto check = [&](int x) {
    int ans = 0;
    F0R(i, N) {
      F0R(j, M) {
        if (A[i][j] >= x) {
          int l = i-1 >= 0 ? dp[i-1][j] : 0;
          int r = j-1 >= 0 ? dp[i][j-1] : 0;
          int c = i-1 >= 0 && j-1 >= 0 ? dp[i-1][j-1] : 0;
          dp[i][j] = min({l, r, c}) + 1;
        }
        else dp[i][j] = 0;
        ckmax(ans, dp[i][j]);
      }
    }

    /*
    if (x == 4) {
      F0R(i, N) {
        F0R(j, N) {
          cout << dp[i][j] << ' ';
        }
        cout << '\n';
      }
    }
    */

    return ans >= x;
  };

  int lo = 1, hi = min(N, M) + 1;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    if (check(mid)) {
      lo = mid;
    }
    else {
      hi = mid;
    }
  }
  return lo;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
