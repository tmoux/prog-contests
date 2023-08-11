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
int N, MOD;

typedef unsigned long long ull;
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(-1ULL / b) {}
  ull reduce(ull a) { // a % b + (0 or b)
    return a - (ull)((__uint128_t(m) * a) >> 64) * b;
  }
};
FastMod RED(1);

void madd(ull& a, ull b) {
  a = RED.reduce(a + b);
}
ull msub(ull a, ull b) {
  madd(a, 2*MOD - b);
  return a;
}
ull mult(ull a, ull b) {
  return RED.reduce(a * b);
}

ull pow2[maxn];
ull dp[maxn], dp2[maxn][maxn<<1];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> MOD;
  RED = FastMod(MOD);
  pow2[0] = 1;
  FOR(i, 1, N+1) pow2[i] = mult(pow2[i-1], 2);

  auto getsum = [&](int i, int l, int r) {
    return msub(dp2[i][r+maxn], dp2[i][l-1+maxn]);
  };

  for (int i = 1; i <= N; i++) {
    if (i <= 1) dp[i] = 1;
    else {
      dp[i] = pow2[i-2];
      for (int j = 1; j < i; j++) {
        auto sub = mult(dp[j], getsum(i-j, j+1, N));
        dp[i] = msub(dp[i], sub);
      }
    }
    for (int j = -N; j <= N; j++) {
      madd(dp2[i][j+maxn], dp2[i][j-1+maxn]);
    }
    madd(dp2[i+1][1-i+maxn], dp[i]);
    for (int j = -i; j <= i; j++) {
      madd(dp2[i+1][j+1+maxn], getsum(i, j, j));
    }
    for (int k = 1; k < i; k++) {
      auto add = mult(dp[k], getsum(i, k+1, N));
      if (i+k+1 <= N) {
        madd(dp2[i+k+1][1-k+maxn], add);
      }
    }
  }
  cout << (dp[N] % MOD) << '\n';
}
