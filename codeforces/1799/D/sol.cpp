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

// Can also just use a (lazy) segtree to perform updates.
struct DP {
  vector<ll> dp;
  multiset<ll> ms;
  ll aux = 0;
  const ll INF = 1e18;

  DP(int K) {
    dp.resize(K+1, INF);
    for (int i = 0; i <= K; i++) ms.insert(INF);
  }

  void set(int i, ll x) {
    auto it = ms.find(dp[i]); ms.erase(it);
    dp[i] = x - aux;
    ms.insert(dp[i]);
  }

  ll get(int i) {
    return dp[i] + aux;
  }

  void add_all(int i, ll x) {
    set(i, get(i) - x);
    aux += x;
  }

  ll get_min() {
    return *ms.begin() + aux;
  }
};

void solve() {
  int N, K; cin >> N >> K;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  vector<int> cold(K+1), hot(K+1);
  for (int i = 1; i <= K; i++) {
    cin >> cold[i];
  }
  for (int i = 1; i <= K; i++) {
    cin >> hot[i];
  }

  DP dp(K);
  dp.set(0, cold[A[0]]);

  for (int i = 0; i+1 < N; i++) {
    ll ndp = dp.get(A[i+1]) + hot[A[i+1]];
    ckmin(ndp, dp.get_min() + cold[A[i+1]]);
    dp.set(A[i], ndp);
    dp.add_all(A[i], A[i] == A[i+1] ? hot[A[i+1]] : cold[A[i+1]]);
  }

  cout << dp.get_min() << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
