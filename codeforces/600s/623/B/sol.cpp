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

const int maxn = 1e6+6;
int N, a, b;

const ll INF = 1e18;
ll cost(int x, int p) {
  if (x % p == 0) return 0;
  else if ((x - 1) % p == 0 || (x + 1) % p == 0) return b;
  else return INF;
}

ll dp[maxn][3];
ll check(const vector<int>& A, int p) {
  F0R(i, N) F0R(j, 3) dp[i][j] = INF;
  dp[0][0] = cost(A[0], p);
  for (int i = 1; i < N; i++) {
    ckmin(dp[i][0], dp[i-1][0] + cost(A[i], p));
    ckmin(dp[i][1], min(dp[i-1][0], dp[i-1][1]) + a);
    ckmin(dp[i][2], min(dp[i-1][1], dp[i-1][2]) + cost(A[i], p));
  }
  return min({dp[N-1][0], dp[N-1][1], dp[N-1][2]});
}

vector<int> primes(int x) {
  vector<int> v;
  int o = x;
  for (int i = 2; i*i <= o; i++) {
    if (x % i == 0) {
      v.push_back(i);
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) v.push_back(x);
  return v;
}

ll solve(const vector<int>& A) {
  ll ans = INF;
  for (int x = A[0]-1; x <= A[0]+1; x++) {
    auto ps = primes(x);
    for (auto p: ps) {
      ckmin(ans, check(A, p));
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> a >> b;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  ll ans = solve(A);
  reverse(all(A));
  ckmin(ans, solve(A));
  cout << ans << '\n';
}
