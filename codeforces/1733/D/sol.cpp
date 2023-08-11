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
  int N; cin >> N;
  int x, y; cin >> x >> y;
  string a, b; cin >> a >> b;
  vector<int> v;
  F0R(i, N) {
    if (a[i] != b[i]) v.push_back(i);
  }
  if (sz(v) % 2) {
    return -1;
  }

  if (x >= y) {
    ll ans = 0;
    if (sz(v) == 2) {
      if (v[0] + 1 == v[1]) ans += min(x, 2*y);
      else ans += y;
    }
    else {
      ans = 1LL * y * (sz(v) / 2);
    }
    return ans;
  }
  else {
    vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(N, vector<ll>(2, 1e18)));
    if (a[0] != b[0]) {
      dp[0][1][0] = y;
      dp[0][0][1] = x;
    }
    else {
      dp[0][0][0] = 0;
    }
    FOR(i, 1, N) {
      F0R(ex, N) {
        if (a[i] != b[i]) {
          if (ex + 1 < N) ckmin(dp[1][ex+1][0], dp[0][ex][0] + y);
          ckmin(dp[1][ex][1], dp[0][ex][0] + x);

          if (ex > 0) ckmin(dp[1][ex-1][0], dp[0][ex][0]);
          ckmin(dp[1][ex][0], dp[0][ex][1]);
        }
        else {
          ckmin(dp[1][ex][1], dp[0][ex][1] + x);
          ckmin(dp[1][ex][0], dp[0][ex][0]);
        }
      }
      swap(dp[0], dp[1]);
      F0R(ex, N) dp[1][ex][0] = dp[1][ex][1] = 1e18;
    }

    return dp[0][0][0];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
