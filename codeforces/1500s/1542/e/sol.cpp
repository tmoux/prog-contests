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

const int maxn = 505;
int N, MOD;

typedef unsigned long long ull;
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(-1ULL / b) {}
  ull reduce(ull a) { // a % b + (0 or b)
    return a - (ull)((__uint128_t(m) * a) >> 64) * b;
  }
};

const int maxx = maxn * maxn;
ull ans[maxn], T[maxn];
ull dp[2][maxx<<1], sum[2][maxx<<1];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> MOD;
  FastMod RED(MOD);
  auto madd = [&](ull& a, ull b) {
    a = RED.reduce(a + b);
  };
  auto msub = [&](ull a, ull b) {
    madd(a, MOD - b);
    return RED.reduce(a);
  };
  auto mult = [&](ull a, ull b) -> ull {
    return RED.reduce(a*b);
  };
  int maxInv = N * (N - 1) / 2;

  auto getsum = [&](int l, int r) -> ull {
    return msub(sum[0][l + maxx], sum[0][r+1 + maxx]);
  };

  dp[0][0 + maxx] = 1;
  for (int i = 1; i <= N; i++) {
    for (int j = maxInv; j >= -maxInv; j--) {
      sum[0][j + maxx] = dp[0][j + maxx];
      madd(sum[0][j + maxx], sum[0][j+1 + maxx]);
    }
    F0R(p, i) {
      FOR(q, p+1, i) {
        madd(T[i], sum[0][1 + q - p + maxx]);
      }
    }

    // for (int j = -maxInv; j <= maxInv; j++) {
    for (int j = -i*(i-1)/2; j <= i*(i-1)/2; j++) {
      dp[1][j + maxx] = 0;
        dp[1][j + maxx] = dp[1][j - 1 + maxx];
        madd(dp[1][j + maxx], getsum(j, j + i - 1));
        dp[1][j + maxx] = msub(dp[1][j + maxx], getsum(j - i, j - 1));
    }

    swap(dp[0], dp[1]);
    swap(sum[0], sum[1]);
  }

  for (int i = 1; i <= N; i++) {
    ans[i] = mult(i, ans[i-1]);
    madd(ans[i], T[i]);
  }

  cout << (ans[N] % MOD) << '\n';
}
