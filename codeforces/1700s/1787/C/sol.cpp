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
  int s; cin >> s;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  vector<int> X(N), Y(N);
  Y[0] = A[0], X[N-1] = A[N-1];
  for (int i = 1; i + 1 < N; i++) {
    int x, y;
    if (A[i] >= s) {
      x = s, y = A[i] - s;
    }
    else {
      x = 0, y = A[i];
    }
    if (x > y) swap(x, y);

    if (A[i-1] <= A[i+1]) {
      X[i] = y, Y[i] = x;
    }
    else {
      X[i] = x, Y[i] = y;
    }
  }

  vector<vector<ll>> dp(N, vector<ll>(2));
  for (int i = 1; i < N; i++) {
    vector<ll> v;
    if (i == 1) v = {A[0], A[0]};
    else v = {Y[i-1], X[i-1]};
    dp[i][0] = min(1LL * X[i] * v[0] + dp[i-1][0],
                   1LL * X[i] * v[1] + dp[i-1][1]);
    dp[i][1] = min(1LL * Y[i] * v[0] + dp[i-1][0],
                   1LL * Y[i] * v[1] + dp[i-1][1]);
  }
  return dp[N-1][0];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
