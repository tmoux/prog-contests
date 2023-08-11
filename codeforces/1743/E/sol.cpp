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

const int maxn = 5005;
ll dp[maxn];

int P1, P2;
ll T1, T2;
int H, s;


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> P1 >> T1;
  cin >> P2 >> T2;
  cin >> H >> s;

  int P = P1 + P2 - s;
  P1 -= s;
  P2 -= s;

  ll ans = 1e18;
  FOR(i, 1, H+1) dp[i] = 1e18;
  FOR(i, 0, H+1) {
    FOR(j, 1, H) {
      ll t = T1 * j;
      if (t >= max(T1, T2)) {
        ll c1 = j - 1;
        ll c2 = t / T2 - 1;
        ckmin(dp[i], dp[max(0LL, i - P1 * c1 - P2 * c2 - P)] + t);
      }
    }

    FOR(j, 1, H) {
      ll t = T2 * j;
      if (t >= max(T1, T2)) {
        ll c1 = t / T1 - 1;
        ll c2 = j - 1;
        ckmin(dp[i], dp[max(0LL, i - P1 * c1 - P2 * c2 - P)] + t);
      }
    }

    FOR(j, 1, H+1) {
      ll t = T1 * j;
      ll c1 = j;
      ll c2 = t / T2;
      if (i + P1 * c1 + P2 * c2 >= H) {
        ckmin(ans, dp[i] + t);
      }
    }

    FOR(j, 1, H+1) {
      ll t = T2 * j;
      ll c1 = t / T1;
      ll c2 = j;
      if (i + P1 * c1 + P2 * c2 >= H) {
        ckmin(ans, dp[i] + t);
      }
    }
  }
  ckmin(ans, dp[H]);

  cout << ans << '\n';
}
